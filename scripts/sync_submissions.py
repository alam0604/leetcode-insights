#!/usr/bin/env python3
"""Add this week's accepted LeetCode submissions to the topic folders in problems/.

Runs weekly from .github/workflows/sync-submissions.yml.

How it works:
  1. Reads your recent accepted submissions (LeetCode keeps the latest 20 public).
  2. Keeps the ones from the last LOOKBACK_DAYS days that aren't in problems/ yet
     (a problem already in any folder is never touched, so hand-picked work is safe).
  3. Picks a folder from the problem's LeetCode topic tags (see FOLDER_PRIORITY).
     Problems that match none of the 12 topics are skipped and listed in the log.
  4. Writes <folder>/<NNNN-slug>/solution.<ext> and README.md, adds a row to the
     folder README, and refreshes the counts in the main README.

Secrets (repository secrets, never stored in the repo):
  LEETCODE_USERNAME   your LeetCode username
  LEETCODE_SESSION    the LEETCODE_SESSION cookie from a logged-in browser
  LEETCODE_CSRF       the csrftoken cookie from the same browser
Reading submission code needs a login, which is why the two cookies are needed.
They expire every few weeks; when they do this script fails loudly so you notice.

Local dry run:  python scripts/sync_submissions.py --dry-run
"""
import datetime as dt
import json
import os
import re
import sys
import time
import urllib.request
from zoneinfo import ZoneInfo

PROBLEMS = "problems"
README = "README.md"
TZ = ZoneInfo("Asia/Kolkata")
LOOKBACK_DAYS = int(os.environ.get("LOOKBACK_DAYS", "8"))  # 7 + 1 day of slack for late cron runs

# folder -> LeetCode topic tags that send a problem there
FOLDER_TAGS = {
    "01-linked-list": {"Linked List", "Doubly-Linked List"},
    "02-backtracking": {"Backtracking"},
    "03-sliding-window": {"Sliding Window"},
    "04-graph": {"Graph", "Graph Theory", "Topological Sort", "Shortest Path",
                 "Union Find", "Union-Find", "Minimum Spanning Tree",
                 "Strongly Connected Component", "Eulerian Circuit", "Biconnected Component"},
    "05-bit-manipulation": {"Bit Manipulation", "Bitmask"},
    "06-stack": {"Stack", "Monotonic Stack"},
    "07-two-pointers": {"Two Pointers"},
    "08-binary-search": {"Binary Search"},
    "09-tree": {"Tree", "Binary Tree", "Binary Search Tree"},
    "10-greedy": {"Greedy"},
    "11-string": {"String"},
    "12-dynamic-programming": {"Dynamic Programming"},
}
# when a problem has several matching tags, the first folder in this list wins.
# This order reproduces 117 of the 122 hand-picked placements already in problems/:
# specific techniques first, the broad catch-alls (String, DP) last.
FOLDER_PRIORITY = [
    "03-sliding-window", "04-graph", "05-bit-manipulation", "01-linked-list",
    "06-stack", "08-binary-search", "07-two-pointers", "02-backtracking",
    "10-greedy", "09-tree", "11-string", "12-dynamic-programming",
]

DIFF_BADGE = {"Easy": "🟢 Easy", "Medium": "🟡 Medium", "Hard": "🔴 Hard"}

EXT = {
    "cpp": "cpp", "c": "c", "java": "java", "python": "py", "python3": "py",
    "pythondata": "py", "pandas": "py", "csharp": "cs", "javascript": "js",
    "typescript": "ts", "golang": "go", "kotlin": "kt", "swift": "swift",
    "rust": "rs", "ruby": "rb", "scala": "scala", "php": "php", "dart": "dart",
    "racket": "rkt", "erlang": "erl", "elixir": "ex", "bash": "sh",
    "mysql": "sql", "mssql": "sql", "oraclesql": "sql", "postgresql": "sql",
}


# ---------------------------------------------------------------- fetching ---

def gql(query, variables, auth=False):
    headers = {
        "Content-Type": "application/json",
        "Referer": "https://leetcode.com/",
        "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
                      "(KHTML, like Gecko) Chrome/130 Safari/537.36",
    }
    if auth:
        session, csrf = os.environ.get("LEETCODE_SESSION"), os.environ.get("LEETCODE_CSRF")
        if not session or not csrf:
            sys.exit("LEETCODE_SESSION and LEETCODE_CSRF secrets are needed to read submission code.")
        headers["Cookie"] = f"LEETCODE_SESSION={session}; csrftoken={csrf}"
        headers["x-csrftoken"] = csrf
    req = urllib.request.Request("https://leetcode.com/graphql",
                                 data=json.dumps({"query": query, "variables": variables}).encode(),
                                 headers=headers)
    for attempt in range(3):
        try:
            with urllib.request.urlopen(req, timeout=30) as r:
                data = json.load(r)
            break
        except Exception:
            if attempt == 2:
                raise
            time.sleep(5 * (attempt + 1))
    if data.get("errors"):
        raise RuntimeError(data["errors"][0].get("message", "GraphQL error"))
    return data["data"]


RECENT_QUERY = """query($u: String!, $n: Int!) {
  recentAcSubmissionList(username: $u, limit: $n) { id titleSlug timestamp }
}"""

QUESTION_QUERY = """query($slug: String!) {
  question(titleSlug: $slug) {
    questionFrontendId title titleSlug difficulty topicTags { name }
  }
}"""

DETAILS_QUERY = """query($id: Int!) {
  submissionDetails(submissionId: $id) {
    code timestamp statusCode
    runtimeDisplay runtimePercentile memoryDisplay memoryPercentile
    lang { name verboseName }
  }
}"""


def recent_accepted(username):
    rows = gql(RECENT_QUERY, {"u": username, "n": 20})["recentAcSubmissionList"] or []
    cutoff = time.time() - LOOKBACK_DAYS * 86400
    latest = {}  # slug -> newest accepted submission this week
    for r in rows:
        ts = int(r["timestamp"])
        if ts >= cutoff and (r["titleSlug"] not in latest or ts > latest[r["titleSlug"]]["ts"]):
            latest[r["titleSlug"]] = {"id": int(r["id"]), "ts": ts}
    return latest


def submission(sub_id):
    d = gql(DETAILS_QUERY, {"id": sub_id}, auth=True)["submissionDetails"]
    if not d or not d.get("code"):
        sys.exit("LeetCode returned no code for submission "
                 f"{sub_id}. The LEETCODE_SESSION / LEETCODE_CSRF cookies have probably "
                 "expired: copy fresh ones from your browser into the repository secrets.")
    return d


# ---------------------------------------------------------------- repo I/O ---

def existing_numbers():
    nums = set()
    for folder in os.listdir(PROBLEMS):
        path = os.path.join(PROBLEMS, folder)
        if os.path.isdir(path):
            for name in os.listdir(path):
                m = re.match(r"(\d+)-", name)
                if m and os.path.isdir(os.path.join(path, name)):
                    nums.add(int(m.group(1)))
    return nums


def pick_folder(tags):
    for folder in FOLDER_PRIORITY:
        if FOLDER_TAGS[folder] & set(tags):
            return folder
    return None


def pct(x):
    x = round(float(x), 1)
    return f"{int(x)}%" if x.is_integer() else f"{x}%"


def problem_readme(q, d, fname):
    num = int(q["questionFrontendId"])
    day = dt.datetime.fromtimestamp(int(d["timestamp"]), TZ).date().isoformat()
    runtime = d["runtimeDisplay"] + (f" (beats {pct(d['runtimePercentile'])})"
                                     if d.get("runtimePercentile") is not None else "")
    memory = d["memoryDisplay"] + (f" (beats {pct(d['memoryPercentile'])})"
                                   if d.get("memoryPercentile") is not None else "")
    url = f"https://leetcode.com/problems/{q['titleSlug']}/"
    return (f"# {num}. {q['title']}\n\n"
            f"**Difficulty:** {DIFF_BADGE.get(q['difficulty'], q['difficulty'])}  \n"
            f"**Topics:** {', '.join(t['name'] for t in q['topicTags'])}  \n"
            f"**Problem:** [{url}]({url})\n\n"
            f"## My last accepted submission\n\n"
            f"| Language | Accepted on | Runtime | Memory |\n"
            f"|---|---|---|---|\n"
            f"| {d['lang']['verboseName']} | {day} | {runtime} | {memory} |\n\n"
            f"Code: [`{fname}`](./{fname})\n")


ROW_RE = re.compile(r"^\| \d+ \| .*\|$", re.M)


def update_folder_readme(folder, rows):
    path = os.path.join(PROBLEMS, folder, "README.md")
    with open(path, encoding="utf-8") as f:
        md = f.read()
    md = md.rstrip("\n") + "\n" + "\n".join(rows) + "\n"
    table = ROW_RE.findall(md)
    counts = {k: sum(f"| {DIFF_BADGE[k]} |" in r for r in table) for k in DIFF_BADGE}
    md = re.sub(r"\d+ hand-picked problems · .*",
                f"{len(table)} hand-picked problems · {counts['Easy']} easy · "
                f"{counts['Medium']} medium · {counts['Hard']} hard", md, count=1)
    with open(path, "w", encoding="utf-8") as f:
        f.write(md)
    return len(table), counts


def update_main_readme(stats):
    """stats: folder -> (picked, {Easy, Medium, Hard}) for every folder."""
    with open(README, encoding="utf-8") as f:
        md = f.read()
    for folder, (picked, c) in stats.items():
        md = re.sub(rf"(\| \[[^\]]+\]\(\./problems/{re.escape(folder)}/\) \| [^|]+ \| )\d+ \| [^|]+ \|",
                    lambda m: f"{m.group(1)}{picked} | {c['Easy']} / {c['Medium']} / {c['Hard']} |",
                    md, count=1)
    total = sum(p for p, _ in stats.values())
    md = re.sub(r"^\d+ problems, 10 per topic and no repeats across topics\.",
                f"{total} problems, no repeats across topics.", md, count=1, flags=re.M)
    md = re.sub(r"^\d+ problems, no repeats across topics\.",
                f"{total} problems, no repeats across topics.", md, count=1, flags=re.M)
    with open(README, "w", encoding="utf-8") as f:
        f.write(md)


def folder_stats():
    stats = {}
    for folder in FOLDER_TAGS:
        with open(os.path.join(PROBLEMS, folder, "README.md"), encoding="utf-8") as f:
            table = ROW_RE.findall(f.read())
        stats[folder] = (len(table), {k: sum(f"| {DIFF_BADGE[k]} |" in r for r in table)
                                      for k in DIFF_BADGE})
    return stats


# -------------------------------------------------------------------- main ---

def main():
    dry = "--dry-run" in sys.argv
    username = os.environ.get("LEETCODE_USERNAME")
    if not username:
        sys.exit("Set the LEETCODE_USERNAME secret.")

    recent = recent_accepted(username)
    have = existing_numbers()
    print(f"{len(recent)} problem(s) accepted in the last {LOOKBACK_DAYS} days.")

    new_rows, added, skipped = {}, [], []
    for slug, sub in sorted(recent.items(), key=lambda kv: kv[1]["ts"]):
        q = gql(QUESTION_QUERY, {"slug": slug})["question"]
        num = int(q["questionFrontendId"])
        if num in have:
            print(f"  already in repo: {num}. {q['title']}")
            continue
        folder = pick_folder([t["name"] for t in q["topicTags"]])
        if not folder:
            skipped.append(f"{num}. {q['title']} ({', '.join(t['name'] for t in q['topicTags']) or 'no tags'})")
            continue
        d = submission(sub["id"])
        ext = EXT.get(d["lang"]["name"], "txt")
        dirname = f"{num:04d}-{slug}"
        fname = f"solution.{ext}"
        print(f"  + {folder}/{dirname} ({d['lang']['verboseName']}, {d['runtimeDisplay']})")
        added.append(f"{num}. {q['title']}")
        if dry:
            continue
        os.makedirs(os.path.join(PROBLEMS, folder, dirname), exist_ok=True)
        with open(os.path.join(PROBLEMS, folder, dirname, fname), "w", encoding="utf-8") as f:
            f.write(d["code"].rstrip("\n") + "\n")
        with open(os.path.join(PROBLEMS, folder, dirname, "README.md"), "w", encoding="utf-8") as f:
            f.write(problem_readme(q, d, fname))
        new_rows.setdefault(folder, []).append(
            f"| {num} | [{q['title']}](./{dirname}/) | {DIFF_BADGE.get(q['difficulty'], q['difficulty'])} "
            f"| {d['lang']['verboseName']} | {d['runtimeDisplay']} | [code](./{dirname}/{fname}) |")
        have.add(num)

    for folder, rows in new_rows.items():
        update_folder_readme(folder, rows)
    if new_rows:
        update_main_readme(folder_stats())

    for s in skipped:
        print(f"  skipped, matches none of the 12 topics: {s}")
    print(f"{'Would add' if dry else 'Added'} {len(added)} problem(s).")
    # tell the workflow what to put in the commit message
    out = os.environ.get("GITHUB_OUTPUT")
    if out and added:
        with open(out, "a", encoding="utf-8") as f:
            f.write(f"added={len(added)}\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
