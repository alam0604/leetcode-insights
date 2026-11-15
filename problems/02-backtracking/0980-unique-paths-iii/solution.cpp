// 980. Unique Paths III  [Hard]
// https://leetcode.com/problems/unique-paths-iii/
// Accepted 2022-06-01 · Runtime 0 ms · Memory 7.1 MB

#define vc vector
class Solution {
public:
    int counter;
    int visited[21][21];
    int uniquePathsIII(vector<vector<int>>& g) {
        int n = g.size(), m = g[0].size();
        int total = 0;
        
        pair<int, int> start, end;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(g[i][j] == 1) start = {i, j};
                else if(g[i][j] == 2) end = {i, j};
                if(g[i][j] == 0) total += 1;
            }
        }
        counter = 0;
        memset(visited, 0, sizeof visited);
        dfs(start.first, start.second, g, end, total);
        return counter;
    }
    
    void dfs(int x, int y, vc<vc<int>> &g, pair<int, int> end, int total) {
        if(x == end.first and y == end.second) {
            if(total == 0) counter += 1;
            return;
        }
        int n = g.size(), m = g[0].size();
        if(x < 0 or x >= n or y < 0 or y >= m) return;
        if(visited[x][y] or g[x][y] == -1) return;
        
        visited[x][y] = 1;
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        if(g[x][y] == 0) total -= 1;
        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            dfs(nx, ny, g, end, total);
        }
        visited[x][y] = 0;
    }
};
