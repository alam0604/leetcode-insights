// 45. Jump Game II  [Medium]
// https://leetcode.com/problems/jump-game-ii/
// Accepted 2024-03-27 · Runtime 128 ms · Memory 19 MB

class Solution {
public:
    int dp[10001];
    int jump(vector<int>& nums) {
        memset(dp, -1, sizeof dp);
        int n = nums.size(); dp[n - 1] = 0; 
        fun(nums, n - 2);
        return dp[0];
    }
    
    void fun(vector<int> &nums, int i) {
        if(i < 0) return;
        
        int mn = INT_MAX;
        for(int j = 0; j <= nums[i]; j++) {
            if(j + i >= nums.size()) break;
            if(dp[i + j] != -1) mn = min(mn, dp[i + j]);
        }
        if(mn != INT_MAX) dp[i] = mn + 1;
        fun(nums, i - 1);
    }
};
