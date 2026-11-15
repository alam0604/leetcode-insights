// 123. Best Time to Buy and Sell Stock III  [Hard]
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
// Accepted 2023-02-23 · Runtime 231 ms · Memory 87.3 MB

class Solution {
public:
    int dp[100001][3][2];
    int maxProfit(vector<int>& prices) {
        memset(dp, -1, sizeof dp);
        return fun(prices, 0, 2, 0);
    }

    int fun(vector<int> &v, int i, int k, int f) {
        if(i >= v.size()) return 0;
        if(k == 0) return 0;
        if(dp[i][k][f] != -1) return dp[i][k][f];
        int x = 0, y = 0;
        if(f) {
            x = v[i] + fun(v, i + 1, k - 1, 0);
            y = fun(v, i + 1, k, f);
        }
        else {
            x = -v[i] + fun(v, i + 1, k, 1);
            y = fun(v, i + 1, k, f);
        }

        return dp[i][k][f] = max(x, y);
    }
};
