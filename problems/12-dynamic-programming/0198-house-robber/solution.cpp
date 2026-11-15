// 198. House Robber  [Medium]
// https://leetcode.com/problems/house-robber/
// Accepted 2026-05-17 · Runtime 0 ms · Memory 10.4 MB

class Solution {
public:
    int rob(vector<int>& nums) {
        unordered_map<int, int> dp;
        dp[0] = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            int a = dp[i - 2] + nums[i];
            int b = dp[i - 1];
            dp[i] = max(a, b);
        }
        return dp[nums.size() - 1];
    }
};
