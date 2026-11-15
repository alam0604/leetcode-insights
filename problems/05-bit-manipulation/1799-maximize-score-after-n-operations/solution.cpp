// 1799. Maximize Score After N Operations  [Hard]
// https://leetcode.com/problems/maximize-score-after-n-operations/
// Accepted 2023-05-15 · Runtime 458 ms · Memory 8.9 MB

class Solution {
public:
    vector<int> dp;
    int maxScore(vector<int>& nums) {
        int n = size(nums), mask = (1 << n) - 1;
        dp.resize(mask + 1, -1);
        return fun(nums, mask, n >> 1);
    }

    int fun(vector<int> &nums, int mask, int n) {
        if(!n) return 0;
        if(dp[mask] != -1) return dp[mask];
        int mx_val = 0;
        for(int i = 0; i < size(nums); i++) {
            for(int j = 0; j < size(nums); j++) {
                if((mask & (1 << i)) and (mask & (1 << j)) and i != j) {
                    int val = n * __gcd(nums[i], nums[j]) + fun(nums, mask ^ (1 << i) ^ (1 << j), n - 1);
                    mx_val = max(mx_val, val);
                }
            }
        }
        return dp[mask] = mx_val;
    }
};
