#!/usr/bin/env python3
"""Refresh the LeetCode Insights README and charts from live LeetCode data.

The username comes from the LEETCODE_USERNAME environment variable (a repository
secret), so it never appears in the repo. Everything is read from LeetCode's
public GraphQL API; no login is needed.

What gets refreshed:
  assets/overview.svg, heatmap.svg, topics.svg, languages.svg, yearly.svg
  README.md: headline numbers, consistency bullets, the all-topics table, the
  difficulty split, the "Solved in topic" column and the snapshot date.

The hand-picked solutions in problems/ are never touched. If LeetCode can't be
reached, nothing is changed.
"""
import datetime as dt
import json
import math
import os
import re
import sys
import urllib.request
from zoneinfo import ZoneInfo

ASSETS = "assets"
README = "README.md"
TZ = ZoneInfo("Asia/Kolkata")

FONT = "Segoe UI, Ubuntu, Helvetica, Arial, sans-serif"
CARD, BORDER, INSET, TRACK = "#161b22", "#30363d", "#0d1117", "#21262d"
INK, SUB, MUTED = "#e6edf3", "#9da7b3", "#6e7681"
EASY, MED, HARD = "#2fbfa0", "#f5a524", "#ef4743"
ACCENT, ACCENT_DIM = "#f5a524", "#a8701a"
HEAT = ["#1c2128", "#3b2a0e", "#6b4a12", "#a8701a", "#f5a524"]
LANG_COLORS = ["#f5a524", "#2fbfa0", "#6ea8fe", "#c792ea", "#ef4743", "#9da7b3"]

# picked-topic names in the README that are spelled differently on LeetCode
TOPIC_ALIASES = {"Graph": "Graph Theory"}


# ---------------------------------------------------------------- fetching ---

def gql(query, variables):
    req = urllib.request.Request(
        "https://leetcode.com/graphql",
        data=json.dumps({"query": query, "variables": variables}).encode(),
        headers={
            "Content-Type": "application/json",
            "Referer": "https://leetcode.com/",
            "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
                          "(KHTML, like Gecko) Chrome/130 Safari/537.36",
        },
    )
    with urllib.request.urlopen(req, timeout=30) as r:
        data = json.load(r)
    if data.get("errors"):
        raise RuntimeError(data["errors"][0].get("message", "GraphQL error"))
    return data["data"]


MAIN_QUERY = """query($u: String!) {
  matchedUser(username: $u) {
    submitStatsGlobal { acSubmissionNum { difficulty count } }
    languageProblemCount { languageName problemsSolved }
    tagProblemCounts {
      fundamental { tagName problemsSolved }
      intermediate { tagName problemsSolved }
      advanced { tagName problemsSolved }
    }
    userCalendar { activeYears }
  }
  userContestRanking(username: $u) { rating attendedContestsCount topPercentage }
}"""

YEAR_QUERY = """query($u: String!, $y: Int) {
  matchedUser(username: $u) { userCalendar(year: $y) { submissionCalendar } }
}"""


def fetch(username):
    d = gql(MAIN_QUERY, {"u": username})
    u = d["matchedUser"]
    solved = {r["difficulty"]: int(r["count"]) for r in u["submitStatsGlobal"]["acSubmissionNum"]}
    tags = []
    for level in ("fundamental", "intermediate", "advanced"):
        tags += [(t["tagName"], int(t["problemsSolved"])) for t in u["tagProblemCounts"][level]]
    langs = [(l["languageName"], int(l["problemsSolved"])) for l in u["languageProblemCount"]]
    calendar = {}
    for year in sorted(u["userCalendar"]["activeYears"]):
        y = gql(YEAR_QUERY, {"u": username, "y": year})
        raw = json.loads(y["matchedUser"]["userCalendar"]["submissionCalendar"] or "{}")
        for ts, n in raw.items():
            day = dt.datetime.fromtimestamp(int(ts), dt.timezone.utc).date()
            calendar[day] = calendar.get(day, 0) + int(n)
    return {"solved": solved, "tags": tags, "langs": langs,
            "contest": d.get("userContestRanking"), "calendar": calendar}


# ----------------------------------------------------------------- numbers ---

def nice_date(d):
    return f"{d:%b} {d.day}, {d.year}"


def date_range(a, b):
    if a.year == b.year:
        return f"{a:%b} {a.day} – {b:%b} {b.day}, {b.year}"
    return f"{nice_date(a)} – {nice_date(b)}"


def analyse(data):
    cal = {d: n for d, n in data["calendar"].items() if n > 0}
    days = sorted(cal)
    best = (0, None, None)
    run_start = prev = None
    for d in days:
        if prev is None or (d - prev).days != 1:
            run_start = d
        length = (d - run_start).days + 1
        if length > best[0]:
            best = (length, run_start, d)
        prev = d
    busiest = min(days, key=lambda d: (-cal[d], d)) if days else None
    weekday_subs = [0] * 7
    for d, n in cal.items():
        weekday_subs[d.weekday()] += n
    weekday = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
               "Sunday"][max(range(7), key=lambda i: weekday_subs[i])] if days else "—"
    years = {}
    for d, n in cal.items():
        subs, active = years.get(d.year, (0, 0))
        years[d.year] = (subs + n, active + 1)
    tags = sorted(data["tags"], key=lambda t: -t[1])  # stable: keeps LeetCode's order on ties
    tags = [t for t in tags if t[1] > 0]
    langs = sorted([l for l in data["langs"] if l[1] > 0], key=lambda l: -l[1])
    return {
        "cal": cal, "streak": best, "busiest": busiest, "weekday": weekday,
        "active_days": len(days), "total_subs": sum(cal.values()),
        "years": dict(sorted(years.items())), "tags": tags, "langs": langs,
    }


# -------------------------------------------------------------------- SVGs ---

def num(x):
    return str(int(x)) if float(x).is_integer() else str(x)


def text(x, y, s, size, fill, weight=400, anchor="start"):
    return (f'<text x="{num(x)}" y="{num(y)}" font-size="{size}" fill="{fill}" '
            f'font-weight="{weight}" text-anchor="{anchor}">{s}</text>')


def frame(w, h, title, right=None, right_size=12, right_fill=SUB):
    out = (f'<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="{h}" viewBox="0 0 {w} {h}" '
           f'font-family="{FONT}"><rect x="0.5" y="0.5" width="{w - 1}" height="{h - 1}" rx="12" '
           f'fill="{CARD}" stroke="{BORDER}"/>' + text(28, 40, title, 18, INK, 700))
    if right:
        out += text(w - 28, 40, right, right_size, right_fill, 400, "end")
    return out


def overview_svg(so, a, contest):
    w, h, cx, cy, r = 860, 210, 110, 125, 58
    c = 2 * math.pi * r
    total = max(so["All"], 1)
    out = frame(w, h, "LeetCode at a glance")
    off = 0.0
    for k, col in (("Easy", EASY), ("Medium", MED), ("Hard", HARD)):
        seg = c * so[k] / total
        if seg > 0:
            out += (f'<circle cx="{cx}" cy="{cy}" r="{r}" fill="none" stroke="{col}" stroke-width="12" '
                    f'stroke-dasharray="{max(seg - 3, 0.1):.1f} {c - seg + 3:.1f}" '
                    f'stroke-dashoffset="{(-off if off else 0.0):.1f}" transform="rotate(-90 {cx} {cy})"/>')
        off += seg
    out += text(cx, cy + 4, so["All"], 30, INK, 700, "middle")
    out += text(cx, cy + 24, "solved", 12, SUB, 400, "middle")
    widest = max(so["Easy"], so["Medium"], so["Hard"], 1)
    for i, (k, col) in enumerate((("Easy", EASY), ("Medium", MED), ("Hard", HARD))):
        y = 85 + 40 * i
        out += (text(205, y, k, 12, SUB) + text(395, y, so[k], 12, INK, 600, "end")
                + f'<rect x="205" y="{y + 7}" width="190" height="7" rx="3.5" fill="{TRACK}"/>'
                + f'<rect x="205" y="{y + 7}" width="{190 * so[k] / widest:.1f}" height="7" rx="3.5" fill="{col}"/>')

    length, s, e = a["streak"]
    if contest and contest.get("rating"):
        rating = str(round(contest["rating"]))
        rating_sub = f"Top {contest['topPercentage']}% · {contest['attendedContestsCount']} contests"
    else:
        rating, rating_sub = "—", "no rated contests yet"
    boxes = [
        ("MAX STREAK", f"{length} days" if length else "—", ACCENT, date_range(s, e) if s else ""),
        ("CONTEST RATING", rating, INK, rating_sub),
        ("ACTIVE DAYS", f"{a['active_days']}", INK, f"{a['total_subs']:,} submissions"),
        ("BUSIEST DAY", f"{a['cal'][a['busiest']]} submissions" if a["busiest"] else "—", INK,
         nice_date(a["busiest"]) if a["busiest"] else ""),
    ]
    for i, (label, value, colour, sub) in enumerate(boxes):
        x, y = 440 + 205 * (i % 2), 62 + 72 * (i // 2)
        out += (f'<rect x="{x}" y="{y}" width="190" height="60" rx="8" fill="{INSET}" stroke="{BORDER}"/>'
                + text(x + 14, y + 20, label, 10, MUTED, 600)
                + text(x + 14, y + 40, value, 18, colour, 700)
                + text(x + 14, y + 53, sub, 10, SUB))
    return out + "</svg>\n"


def heat_colour(n):
    if n <= 0:
        return HEAT[0]
    if n <= 2:
        return HEAT[1]
    if n <= 5:
        return HEAT[2]
    if n <= 10:
        return HEAT[3]
    return HEAT[4]


def heatmap_svg(a, years):
    _, streak_start, streak_end = a["streak"]
    cells, max_col = [], 0
    for i, year in enumerate(years):
        top = 90 + 125 * i
        jan1 = dt.date(year, 1, 1)
        cells.append(text(28, top + 26.5, year, 12, SUB, 600))
        d = jan1
        while d.year == year:
            # Monday-first weeks; rows run Monday (top) to Sunday (bottom)
            col, row = ((d - jan1).days + jan1.weekday()) // 7, d.weekday()
            max_col = max(max_col, col)
            n = a["cal"].get(d, 0)
            ring = (' stroke="#ffd27a" stroke-opacity="0.35"'
                    if streak_start and streak_start <= d <= streak_end else "")
            cells.append(f'<rect x="{72 + 15 * col}" y="{top - 30 + 15 * row}" width="12" height="12" rx="2.5" '
                         f'fill="{heat_colour(n)}"{ring}><title>{d.isoformat()}: {n}</title></rect>')
            d += dt.timedelta(days=1)
    w = 72 + 15 * max_col + 12 + 34
    h = 90 + 125 * (len(years) - 1) + 133
    out = frame(w, h, "Submission calendar",
                f"{a['active_days']} active days · {a['streak'][0]}-day max streak")
    out += "".join(cells)
    out += text(w - 118, h - 14, "less", 10, MUTED, 400, "end")
    out += "".join(f'<rect x="{w - 110 + 16 * i}" y="{h - 24}" width="12" height="12" rx="2.5" fill="{c}"/>'
                   for i, c in enumerate(HEAT))
    out += text(w - 26, h - 14, "more", 10, MUTED)
    return out + "</svg>\n"


def topics_svg(tags):
    top = tags[:20]
    per_col = math.ceil(len(top) / 2) or 1
    widest = max([n for _, n in top] + [1])
    h = 74 + 24 * (per_col - 1) + 32
    out = frame(860, h, "Problems solved by topic", f"top {len(top)} of {len(tags)} topics")
    for i, (name, n) in enumerate(top):
        x0, y = 28 + 404 * (i // per_col), 74 + 24 * (i % per_col)
        out += (text(x0, y, name, 12, INK)
                + f'<rect x="{x0 + 170}" y="{y - 9}" width="170" height="12" rx="3" fill="{TRACK}"/>'
                + f'<rect x="{x0 + 170}" y="{y - 9}" width="{170 * n / widest:.1f}" height="12" rx="3" '
                  f'fill="{ACCENT}" fill-opacity="{0.45 + 0.55 * n / widest:.2f}"/>'
                + text(x0 + 376, y + 1, n, 12, INK, 600, "end"))
    return out + "</svg>\n"


def side_height(n_langs, n_years):
    return max(282, 94 + 26 * (n_langs - 1) + 58, 78 + 26 * (n_years - 1) + 48)


def languages_svg(langs, h):
    langs = langs[:len(LANG_COLORS)]
    total = sum(n for _, n in langs) or 1
    out = frame(420, h, "Languages")
    out += ('<clipPath id="c"><rect x="28" y="58" width="364" height="10" rx="5"/></clipPath>'
            '<g clip-path="url(#c)">')
    x = 28.0
    for (name, n), col in zip(langs, LANG_COLORS):
        seg = max(364 * n / total, 2)
        out += f'<rect x="{x:.1f}" y="58" width="{seg:.1f}" height="10" fill="{col}"/>'
        x += seg
    out += "</g>"
    for i, ((name, n), col) in enumerate(zip(langs, LANG_COLORS)):
        y = 94 + 26 * i
        out += (f'<circle cx="34" cy="{y}" r="5" fill="{col}"/>'
                + text(46, y + 4, name, 13, INK)
                + text(330, y + 4, f"{n} solved", 12, SUB, 400, "end")
                + text(392, y + 4, f"{100 * n / total:.1f}%", 12, INK, 600, "end"))
    return out + "</svg>\n"


def yearly_svg(years_stats, h):
    out = frame(420, h, "Submissions per year", "subs · active days", 11, MUTED)
    peak = max([s for s, _ in years_stats.values()] + [1])
    for i, (year, (subs, active)) in enumerate(years_stats.items()):
        y = 78 + 26 * i
        bar = 200 * subs / peak
        out += (text(28, y, year, 13, SUB)
                + f'<rect x="72" y="{y - 10}" width="{max(bar, 5):.1f}" height="13" rx="3" '
                  f'fill="{ACCENT if subs == peak else ACCENT_DIM}"/>'
                + text(72 + bar + 8, y + 1, f"{subs} · {active}d", 11, INK))
    return out + "</svg>\n"


# ------------------------------------------------------------------ README ---

def patch(md, pattern, repl, flags=0):
    new, count = re.subn(pattern, repl, md, count=1, flags=flags)
    if not count:
        print(f"note: README section not found for /{pattern[:40]}.../, left as is")
    return new


def update_readme(md, so, a, contest):
    length, s, e = a["streak"]
    rating = (f"{round(contest['rating'])} contest rating (top {contest['topPercentage']}%)"
              if contest and contest.get("rating") else "no contest rating yet")
    md = patch(md, r"\*\*\d+ problems solved · .*?\*\*",
               lambda _: f"**{so['All']} problems solved · {length}-day max streak · {rating}**")

    bullets = (f"- **Longest streak:** {length} days in a row, from {nice_date(s)} to {nice_date(e)}\n"
               f"- **Active days:** {a['active_days']} days with {a['total_subs']:,} submissions in total\n"
               f"- **Busiest day:** {nice_date(a['busiest'])}, with {a['cal'][a['busiest']]} submissions\n"
               f"- **Most active weekday:** {a['weekday']}") if s else None
    if bullets:
        md = patch(md, r"- \*\*Longest streak:\*\*.*\n- \*\*Active days:\*\*.*\n"
                       r"- \*\*Busiest day:\*\*.*\n- \*\*Most active weekday:\*\*.*",
                   lambda _: bullets)

    md = patch(md, r"<summary><b>All \d+ topics</b></summary>",
               lambda _: f"<summary><b>All {len(a['tags'])} topics</b></summary>")
    table = "\n".join(f"| {name} | {n} |" for name, n in a["tags"])
    md = patch(md, r"(\| Topic \| Solved \|\n\|---\|---\|\n)(?:\|.*\|\n?)+",
               lambda m: m.group(1) + table + "\n")

    hard_pct = 100 * so["Hard"] / max(so["All"], 1)
    md = patch(md, r"\*\*Difficulty split:\*\*.*",
               lambda _: (f"**Difficulty split:** {so['Easy']} easy · {so['Medium']} medium · "
                          f"{so['Hard']} hard. Hard problems are {hard_pct:.1f}% of all solved."))

    tag_counts = dict(a["tags"])

    def picked_row(m):
        name = m.group(1)
        n = tag_counts.get(TOPIC_ALIASES.get(name, name))
        return m.group(0) if n is None else f"{m.group(1)}](./problems/{m.group(2)}) | {n} |"

    md = re.sub(r"(?<=\| \[)([^\]]+)\]\(\./problems/([^)]+)\) \| \d+ \|", picked_row, md)
    return md


# -------------------------------------------------------------------- main ---

def write_if_changed(path, content):
    old = None
    if os.path.exists(path):
        with open(path, encoding="utf-8") as f:
            old = f.read()
    if old == content:
        return False
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)
    return True


def main():
    username = os.environ.get("LEETCODE_USERNAME", "").strip()
    if not username:
        print("LEETCODE_USERNAME secret is not set; leaving everything as it is.")
        return 0
    try:
        data = fetch(username)
    except Exception as e:  # LeetCode down or blocking us: keep what's there
        print(f"Could not fetch LeetCode data ({type(e).__name__}: {e}); leaving everything as it is.")
        return 0
    return render_all(data)


def render_all(data, today=None):
    so = {k: data["solved"].get(k, 0) for k in ("All", "Easy", "Medium", "Hard")}
    a = analyse(data)
    today = today or dt.datetime.now(TZ).date()
    years = list(range(min(a["years"]) if a["years"] else today.year, today.year + 1))
    h = side_height(len(a["langs"][:len(LANG_COLORS)]), len(a["years"]))

    changed = False
    for name, svg in (("overview", overview_svg(so, a, data["contest"])),
                      ("heatmap", heatmap_svg(a, years)),
                      ("topics", topics_svg(a["tags"])),
                      ("languages", languages_svg(a["langs"], h)),
                      ("yearly", yearly_svg(a["years"], h))):
        changed |= write_if_changed(os.path.join(ASSETS, f"{name}.svg"), svg)

    with open(README, encoding="utf-8") as f:
        md = f.read()
    new_md = update_readme(md, so, a, data["contest"])
    if new_md != md or changed:
        # only move the snapshot date when the numbers actually moved
        new_md = re.sub(r"Stats snapshot: [^<\n]*", f"Stats snapshot: {nice_date(today)}", new_md)
        changed |= write_if_changed(README, new_md)

    print(f"{'Updated' if changed else 'No change'}: {so['All']} solved, "
          f"{a['active_days']} active days, {a['streak'][0]}-day max streak.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
