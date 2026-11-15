// 2360. Longest Cycle in a Graph  [Hard]
// https://leetcode.com/problems/longest-cycle-in-a-graph/
// Accepted 2022-07-31 · Runtime 280 ms · Memory 98.7 MB

class Solution {
public:
    int vis[100005], dist[100005];
    int longestCycle(vector<int>& edges) {
        
        int n = edges.size();
        
        memset(vis, 0, sizeof vis);
        memset(dist, 0, sizeof dist);
        
        int cycle_len = -1;
        vector<int> stack(n, 0);
        for(int i = 0; i < n; i++) {
            if(!vis[i])
                cycle(edges, i, stack, cycle_len, 0);
        }
        return cycle_len;
    }
    
    
    void cycle(vector<int> &edges, int s, vector<int> &st, int &cycle_len, int len) {
        
        if(s == -1) return;
        if(vis[s]) {
            if(st[s])
                cycle_len = max(cycle_len, len - dist[s]);
            return;
        }
        
        dist[s] = len;
        vis[s] = st[s] = 1;
        
        cycle(edges, edges[s], st, cycle_len, len + 1);
        st[s] = 0;
    }
    
};
