// 1579. Remove Max Number of Edges to Keep Graph Fully Traversable  [Hard]
// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
// Accepted 2023-05-01 · Runtime 765 ms · Memory 304.2 MB

class Solution {
public:
    class dsu {
        public:
        int par[100001], rk[100001];
        dsu() {
            for(int i = 0; i < 100001; i++)
                par[i] = i, rk[i] = 1;
        };

        int find(int u) {
            if(u == par[u]) return u;
            return par[u] = find(par[u]);
        }

        bool union_(int u, int v) {
            u = find(u), v = find(v);
            if(u != v) {
                if(rk[v] > rk[u]) swap(u, v);
                par[v] = u; rk[u] += rk[v];
                return true;
            }
            return false;
        }
    };

    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        auto alice = new dsu(), bob = new dsu();
        int alice_edge = 0, bob_edge = 0, discarded_edge = 0;
        for(auto x : edges) {
            if(x[0] == 3) {
                if(alice->union_(x[1], x[2])) {
                    bob->union_(x[1], x[2]);
                    alice_edge += 1, bob_edge += 1;
                }
                else discarded_edge += 1;
            }
        }

        for(auto x : edges) {
            if(x[0] == 1) {
                if(alice->union_(x[1], x[2])) alice_edge += 1;
                else discarded_edge += 1;
            } else if(x[0] == 2) {
                if(bob->union_(x[1], x[2])) bob_edge += 1;
                else discarded_edge += 1;
            }
        }
        return (alice_edge == n - 1 and bob_edge == n - 1) ? discarded_edge : -1;
    }
};
