// 1697. Checking Existence of Edge Length Limited Paths  [Hard]
// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/
// Accepted 2023-04-29 · Runtime 674 ms · Memory 110 MB

#define vc vector
class Solution {
public:
    int par[100005], rk[100005];
    int find(int u) {
        if(u == par[u]) return u;
        return par[u] = find(par[u]);
    }
    void union_(int u, int v) {
        u = find(u), v = find(v);
        if(u != v) {
            if(rk[v] > rk[u]) swap(u, v);
            par[v] = u; rk[u] += rk[v];
        }
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& el, vector<vector<int>>& q) {
        sort(begin(el), end(el), [](const vc<int> &a, const vc<int> &b) {
            return a[2] < b[2]; });
        for(int i = 0; i < q.size(); i++)
            q[i].push_back(i);
        sort(begin(q), end(q), [](const vc<int> &a, const vc<int> &b) {
            return a[2] < b[2]; });
        for(int i = 0; i < 100005; i++) par[i] = i, rk[i] = 0;

        int wt = q[0][2], i = 0, f = 0, k = 0;
        vc<bool> res(size(q), 0);
        while(i < size(el) and k < size(q)) {
            if(el[i][2] < wt) {
                union_(el[i][0], el[i][1]);
                i += 1;
            }
            else {
                if(k == size(q) - 1) f = 1;
                if(find(q[k][0]) == find(q[k][1]))
                     res[q[k][3]] = true;
                k += 1;
                if(k < size(q))
                    wt = q[k][2];
                else break;
            }
        }
        if(!f) {
            while(k < size(q)) {
                if(find(q[k][0]) == find(q[k][1]))
                    res[q[k][3]] = 1;
                k += 1;
            }
        }
        return res;
    }
};
