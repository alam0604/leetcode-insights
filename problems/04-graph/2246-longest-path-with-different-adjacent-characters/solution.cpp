// 2246. Longest Path With Different Adjacent Characters  [Hard]
// https://leetcode.com/problems/longest-path-with-different-adjacent-characters/
// Accepted 2023-01-13 · Runtime 627 ms · Memory 229.9 MB

class Solution {
public:
    int maxPathLength;
    int vis[100005];
    int longestPath(vector<int>& parent, string s) {
        vector<vector<int>> g(size(s));
        for(int i = 1; i < parent.size(); i++)
            g[parent[i]].push_back(i), g[i].push_back(parent[i]);
        maxPathLength = 0;
        dfs(g, s, 0);
        return maxPathLength;
    }

    pair<int, char> dfs(vector<vector<int>> &g, string &s, int src) {
        vector<pair<int, char>> vc;
        vis[src] = 1;
        int a = 0, b = 0;
        for(auto x : g[src]) {
            if(!vis[x]) {
                pair<int, char> temp = dfs(g, s, x);
                if(temp.second != s[src]) {
                    if(temp.first >= a) {
                        b = a;
                        a = temp.first;
                    }
                    else b = max(b, temp.first);
                }
            }
        }
        maxPathLength = max(maxPathLength, a + b + 1);
        return {max(a, b) + 1, s[src]};
    }
};
