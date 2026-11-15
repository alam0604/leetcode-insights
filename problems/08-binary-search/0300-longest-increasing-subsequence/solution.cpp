// 300. Longest Increasing Subsequence  [Medium]
// https://leetcode.com/problems/longest-increasing-subsequence/
// Accepted 2026-05-21 · Runtime 467 ms · Memory 41.6 MB

class Solution {
public:
    int dp[2505][2505];
    int lengthOfLIS(vector<int>& nums) {
        memset(dp, -1, sizeof dp);
        return lis(nums, 0, -1);
    }

    int lis(vector<int> &nums, int i, int prev) {
        if(i >= nums.size()) return 0;
        if(dp[i][prev + 1] != -1) return dp[i][prev + 1];
        int a, b, c; a = b = c = 0;

        if(prev == -1)
            a = 1 + lis(nums, i + 1, i);
        else {
            if(nums[i] > nums[prev])
                a = 1 + lis(nums, i + 1, i);
        }
        // b = lis(nums, i + 1, i);
        c = lis(nums, i + 1, prev);
        return dp[i][prev + 1] = max(a, c);
    }
};
