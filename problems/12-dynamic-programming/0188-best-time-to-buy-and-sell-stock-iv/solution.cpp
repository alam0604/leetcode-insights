// 188. Best Time to Buy and Sell Stock IV  [Hard]
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
// Accepted 2022-09-10 · Runtime 23 ms · Memory 11.8 MB

class Solution {
public:
    int dp[1001][101][2];
    int maxProfit(int k, vector<int>& prices) {
        memset(dp, -1, sizeof dp);
	    return fun(prices, 0, k, 0);
    }
    
    int fun(vector<int> &v, int i, int k, int f) {
        if (i == v.size() or k == 0) return 0;
        if(dp[i][k][f] != -1) return dp[i][k][f];
        if(f) {
            int x = v[i] + fun(v, i + 1, k - 1, 0);
            int y = fun(v, i + 1, k, f);
            return dp[i][k][f] = max(x, y);
        }
        else {
            int x = fun(v, i + 1, k, f ^ 1) - v[i];
            int y = fun(v, i + 1, k, f);
            return dp[i][k][f] = max(x, y);
        }
    }
};
