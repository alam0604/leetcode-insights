// 741. Cherry Pickup  [Hard]
// https://leetcode.com/problems/cherry-pickup/
// Accepted 2022-10-12 · Runtime 329 ms · Memory 38.7 MB

class Solution {
public:
    int dp[51][51][51][51];
    int cherryPickup(vector<vector<int>> &g) {
        memset(dp, -1, sizeof dp);
        int res = fun(g, 0, 0, 0, 0);
        return res < 0 ? 0 : res;
    }
    
    int invalid(int x1, int y1, int x2, int y2, int n, int m) {
        return (x1 < 0 or x2 < 0 or y1 < 0 or y2 < 0 or x1 >= n or x2 >= n or y1 >= m or y2 >= m);
    }
    int fun(vector<vector<int>> &g, int x1, int y1, int x2, int y2) {
        int n = g.size(), m = g[0].size();
        
        if(invalid(x1, y1, x2, y2, n, m) or g[x1][y1] == -1 or g[x2][y2] ==-1)
            return -1e6;
        if(dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
        
        int count = 0;
        if(x1 == x2 and y1 == y2)
            count += g[x1][y1];
        else
            count += (g[x1][y1] + g[x2][y2]);
        if(x1 == n - 1 and x2 == n - 1 and y1 == m - 1 and y2 == m - 1)
            return count;
        
        int a = fun(g, x1, y1 + 1, x2, y2 + 1);
        int b = fun(g, x1 + 1, y1, x2 + 1, y2);
        int c = fun(g, x1 + 1, y1, x2, y2 + 1);
        int d = fun(g, x1, y1 + 1, x2 + 1, y2);
        
        return dp[x1][y1][x2][y2] = count + max({a, b, c, d});
    }
};
