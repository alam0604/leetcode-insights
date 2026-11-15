// 210. Course Schedule II  [Medium]
// https://leetcode.com/problems/course-schedule-ii/
// Accepted 2022-03-30 · Runtime 31 ms · Memory 14.1 MB

class Solution {
public:
    int visited[2005];
    void dfs(vector<vector<int>> &adj, int src, stack<int> &st) {
        visited[src] = 1;
        for(auto &x : adj[src])
            if(not visited[x])
                dfs(adj, x, st);
        st.push(src);
    }
    vector<int> findOrder(int n, vector<vector<int>>& req) {
        vector<vector<int>> adj(n);
        for(auto &x : req)
            adj[x[0]].push_back(x[1]);
        
        memset(visited, 0, sizeof visited);
        if(containsCycle(adj, n)) return {};
        memset(visited, 0, sizeof visited);
        
        stack<int> st; vector<int> res;
        for(int i = 0; i < n; i++)
            if(not visited[i])
                dfs(adj, i, st);
        while(not st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
    
    bool cycle(vector<vector<int>> &adj, int src, vector<int> &st) {
        visited[src] = st[src] = 1;
        for(auto &x : adj[src]) {
            if(not visited[x]) {
                if(cycle(adj, x, st))
                    return true;
            }
            else
                if(st[x]) return true;
        }
        st[src] = 0;
        return false;
    }
    
    bool containsCycle(vector<vector<int>> &adj, int n) {
        vector<int> st(n, 0);
        for(int i = 0; i < n; i++) {
            if(not visited[i])
                if(cycle(adj, i, st))
                    return true;
        }
        return false;
    }
};
