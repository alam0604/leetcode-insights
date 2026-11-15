// 329. Longest Increasing Path in a Matrix  [Hard]
// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
// Accepted 2022-05-19 · Runtime 39 ms · Memory 14.9 MB

class Solution {
    int dp[205][205];
    int dfs(vector<vector<int>>& matrix, int x, int y) {
        
        int n = matrix.size(), m = matrix[0].size();
        if(dp[x][y] != -1) return dp[x][y];
        int mx = 0;
        
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        
        for(int i = 0; i < 4; i++) {
            int nr = x + dx[i];
            int nc = y + dy[i];
            
            if(nr < 0 or nr >= n or nc < 0 or nc >= m) continue;
            if(matrix[nr][nc] <= matrix[x][y]) continue;
            
            int cur = dfs(matrix, nr, nc);
            mx = max(mx, cur);
        }
        
        return dp[x][y] = mx + 1;
    }
    
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        
        int n = matrix.size(), m = matrix[0].size();
        int res = 0;
        memset(dp, -1, sizeof dp);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                res = max(res, dfs(matrix, i, j));
        }
        
        return res;
    }
};
