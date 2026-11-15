// 1192. Critical Connections in a Network  [Hard]
// https://leetcode.com/problems/critical-connections-in-a-network/
// Accepted 2022-05-18 · Runtime 1381 ms · Memory 211.8 MB

class Solution {
public:
    int timer = 1;
    vector<vector<int>> res;
    set<pair<int, int>> st;
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& con) {
        
        vector<vector<int>> adj(n);
        for(auto x : con) {
            adj[x[0]].push_back(x[1]);
            adj[x[1]].push_back(x[0]);
        }
        
        vector<int> in(n, 0), min_time(n, 0);
        vector<int> visited(n, 0);
        dfs(adj, 0, in, min_time, visited, -1);
        
        return res;
    }
    
    void dfs(vector<vector<int>> &adj, int s, vector<int> &in, vector<int> &mn_time, vector<int> &visited, int parent) {
        
        in[s] = mn_time[s] = timer++;
        
        visited[s] = 1;
        
        for(auto x : adj[s]) {
            if(x == parent) continue;
            if(visited[x])
                mn_time[s] = min(mn_time[s], in[x]);
            else {
                dfs(adj, x, in, mn_time, visited, s);
                mn_time[s] = min(mn_time[x], mn_time[s]);
                
                if(mn_time[x] > in[s]) {
                    if(x < s) swap(x, s);
                    if(st.find({s, x}) == st.end()) {
                        res.push_back({s, x});
                        st.insert({s, x});
                    }
                }
            }
        }
    }
};
