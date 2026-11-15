// 53. Maximum Subarray  [Medium]
// https://leetcode.com/problems/maximum-subarray/
// Accepted 2026-02-11 · Runtime 3 ms · Memory 71.6 MB

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int mx_sum = nums[0], sum = 0;
        for(auto x : nums) {
            sum += x;
            mx_sum = max(mx_sum, sum);
            if(sum < 0) sum = 0;
        }
        return mx_sum;
    }
};
