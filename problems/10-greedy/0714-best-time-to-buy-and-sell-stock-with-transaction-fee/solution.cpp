// 714. Best Time to Buy and Sell Stock with Transaction Fee  [Medium]
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
// Accepted 2023-06-22 · Runtime 130 ms · Memory 61.3 MB

class Solution {
public:
    int dp[100005][2];
    int maxProfit(vector<int>& prices, int fee) {
        memset(dp, -1, sizeof dp);
        return fun(prices, fee, 0, 0);
    }

    int fun(vector<int> &prices, int &fee, int f, int i) {
        if(i >= prices.size()) return 0;
        if(dp[i][f] != -1) return dp[i][f];
        int x = 0, y = 0;
        if(f) {
            x = fun(prices, fee, f, i + 1);
            y = prices[i] + fun(prices, fee, f ^ 1, i + 1);
        }
        else {
            x = fun(prices, fee, f, i + 1);
            y = -(fee + prices[i]) + fun(prices, fee, f ^ 1, i + 1);
        }
        return dp[i][f] = max(x, y);
    }
};
