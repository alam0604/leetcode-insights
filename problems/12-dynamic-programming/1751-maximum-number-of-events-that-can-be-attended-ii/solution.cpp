// 1751. Maximum Number of Events That Can Be Attended II  [Hard]
// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/
// Accepted 2023-07-19 · Runtime 306 ms · Memory 72.7 MB

class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(), events.end(), [](vector<int> &a, vector<int> &b) {
            if(a[0] == b[0]) return a[1] < b[1];
            return a[0] < b[0];
        });
        int n = events.size();
        vector<vector<int>> dp(n + 1, vector<int> (k + 1, -1));
        return fun(events, 0, k, dp);
    }
    int binSearch(vector<vector<int>> &events, int l, int target) {
        int res = events.size(), h = res - 1;
        while(l <= h) {
            int m = l + (h - l) / 2;
            if(events[m][0] > target) {
                res = m;
                h = m - 1;
            }
            else l = m + 1;
        }
        return res;
    }
    long fun(vector<vector<int>> &rides, int i, int k, vector<vector<int>> &dp) {
        if(i >= rides.size() or k <= 0) return 0;
        if(dp[i][k] != -1) return dp[i][k];
        long x = fun(rides, i + 1, k, dp);
        long idx = binSearch(rides, i, rides[i][1]);
        long y = rides[i][2] + fun(rides, idx, k - 1, dp);
        return dp[i][k] = max(x, y);
    }
};
