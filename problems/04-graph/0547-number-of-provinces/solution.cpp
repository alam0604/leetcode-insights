// 547. Number of Provinces  [Medium]
// https://leetcode.com/problems/number-of-provinces/
// Accepted 2022-03-16 · Runtime 28 ms · Memory 14.8 MB

class Solution {
public:
    
    void dfs(vector<vector<int>> &g, vector<int> &visited, int s) {
        visited[s] = 1;
        vector<int> adj;
        for(int i = 0; i < g.size(); i++) {
            if(g[s][i])
                adj.push_back(i);
        }
        
        for(auto x : adj) {
            if(not visited[x])
                dfs(g, visited, x);
        }
    }
    int findCircleNum(vector<vector<int>> &g) {
        int n = g.size();
        vector<int> visited(n, 0);
        
        int provinces = 0;
        for(int i = 0; i < n; i++) {
            if(not visited[i]) {
                provinces++;
                dfs(g, visited, i);
            }
        }
        return provinces;
    }
};
