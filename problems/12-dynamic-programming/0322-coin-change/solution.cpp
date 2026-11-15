// 322. Coin Change  [Medium]
// https://leetcode.com/problems/coin-change/
// Accepted 2022-05-21 · Runtime 106 ms · Memory 10.6 MB

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        int dp[n + 1][amount + 1];
        for(int i = 0; i <= n; i++) dp[i][0] = 0;
        for(int i = 0; i <= amount; i++) dp[0][i] = 1e5;
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= amount; j++) {
                if(j >= coins[i - 1])
                    dp[i][j] = min(dp[i - 1][j], 1 + dp[i][j - coins[i - 1]]);
                else dp[i][j] = dp[i - 1][j];
            }
        }
        
        if(dp[n][amount] == 1e5) return -1;
        return dp[n][amount];
    }
};
