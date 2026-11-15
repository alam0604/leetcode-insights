// 2328. Number of Increasing Paths in a Grid  [Hard]
// https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/
// Accepted 2023-06-20 · Runtime 328 ms · Memory 56.6 MB

class Solution {
public:
    typedef long long ll;
    ll dp[1005][1005];
    ll vis[1005][1005];
    const static int mod = 1e9 + 7;
    int countPaths(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        memset(dp, -1, sizeof dp);
        ll res = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++)
                res += fun(g, i, j) % mod;
        }    
        return (res + n * m) % mod;
    }

    ll fun(vector<vector<int>> &g, int i, int j) {
        int m = g.size(), n = g[0].size();
        if(dp[i][j] != -1) return dp[i][j] % mod;
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};

        int res = 0;
        vis[i][j] = 1;
        for(int k = 0; k < 4; k++) {
            int nx = i + dx[k];
            int ny = j + dy[k];

            if(nx < 0 or ny < 0 or nx >= m or ny >= n or vis[nx][ny]) continue;
            if(g[nx][ny] > g[i][j]) {
                int val = 1 + fun(g, nx, ny);
                res += val % mod;
            }
        }
        vis[i][j] = 0;
        return dp[i][j] = res % mod;
    }
};
