// 62. Unique Paths  [Medium]
// https://leetcode.com/problems/unique-paths/
// Accepted 2024-04-10 · Runtime 0 ms · Memory 7.2 MB

class Solution {
public:
  int dp[101][101];
    int uniquePaths(int m, int n) {
      memset(dp, -1, sizeof dp);
        return fun(0, 0, m, n);
    }

    int fun(int i, int j, int &m, int &n) {
      if(i == m - 1 or j == n - 1) return 1;
      if(i >= m or j >= n) return 0;
      if(dp[i][j] != -1) return dp[i][j];
      int x = fun(i + 1, j, m, n);
      int y = fun(i, j + 1, m, n);
      return dp[i][j] = x + y;
    }
};
