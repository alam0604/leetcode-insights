// 847. Shortest Path Visiting All Nodes  [Hard]
// https://leetcode.com/problems/shortest-path-visiting-all-nodes/
// Accepted 2022-04-04 · Runtime 198 ms · Memory 18.1 MB

class Solution {
public:
    class node {
        public:
            int u, level, mask;
            node(int u, int level, int mask) {
                this->u = u, this->level = level, this->mask = mask;
            }
    };
    
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        int allDone = (1 << n) - 1;
        set<pair<int, int>> st; 
        queue<node> q;
        for(int i = 0; i < n; i++) {
            q.push(node(i, 1, (1 << i)));
            st.insert({i, 1 << i});
        }
        while(not q.empty()) {
            node p = q.front(); q.pop();
            
            for(auto x : graph[p.u]) {
                int tmask = p.mask | (1 << x);
                if(tmask == allDone) return p.level;
                if(st.count({x, tmask})) continue;
                else {
                    q.push(node(x, p.level + 1, tmask));
                    st.insert({x, tmask});
                }
            }
        }
        return 0;
    }
};
