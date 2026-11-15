// 2218. Maximum Value of K Coins From Piles  [Hard]
// https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/
// Accepted 2023-04-15 · Runtime 253 ms · Memory 19.6 MB

#define vc vector
class Solution {
public:
    int dp[2005][1005];
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        memset(dp, -1, sizeof dp);
        for(int i = 0; i < piles.size(); i++) {
            for(int j = 1; j < piles[i].size(); j++)
                piles[i][j] += piles[i][j - 1];
        }
        return fun(piles, k, piles.size());
    }

    int fun(vc<vc<int>> &p, int k, int n) {
        if(k == 0 or n <= 0) return 0;
        if(dp[k][n] != -1) return dp[k][n];
        int mx = fun(p, k, n - 1);
        int lim = p[n - 1].size(); lim = min(lim, k);
        for(int j = 1; j <= lim; j++) {
            int val = p[n - 1][j - 1];
            int a = val + fun(p, k - j, n - 1);
            mx = max(mx, a);
        }
        return dp[k][n] = mx;
    }
};
