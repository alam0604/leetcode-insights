class Solution {
public:
    int parent[4000];
    static inline bool comp(vector<int> &a, vector<int> &b) { return a[0] < b[0];}
    
    int find(int x) {
        if(x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    
    bool union_(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) return true;
        parent[y] = x;
        return false;
    }
    
    int swimInWater(vector<vector<int>>& g) {
        int n = g.size();
        vector<vector<int>> edges;
        for(int i = 0; i < 4000; i++)
            parent[i] = i;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                edges.push_back({g[i][j], i, j});
            }
        }
        
        sort(edges.begin(), edges.end());
        
        for(int i = 0; i < edges.size(); i++) {
            vector<int> p = edges[i];
            int x = p[1];
            int y = p[2];
            
            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, 1, 0, -1};
            
            for(int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                
                if(nx < 0 or nx >= n or ny < 0 or ny >= n)
                    continue;
                if(g[nx][ny] <= g[x][y]) 
                    union_(x * n + y, nx * n + ny);
            }
            
            if(find(0) == find(n * n - 1))
                return g[x][y];
        }
        return -1;
    }
};
