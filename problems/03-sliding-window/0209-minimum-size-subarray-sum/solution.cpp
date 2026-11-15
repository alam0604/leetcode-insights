// 209. Minimum Size Subarray Sum  [Medium]
// https://leetcode.com/problems/minimum-size-subarray-sum/
// Accepted 2026-02-11 · Runtime 0 ms · Memory 32.1 MB

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int l = 0, r = 0, sum = 0, min_len = nums.size() + 1;
        while(r < nums.size()) {
            sum += nums[r];
            while(sum >= target) {
                min_len = min(min_len, r - l + 1);
                sum -= nums[l++];
            }
            r += 1;
        }
        while(sum >= target) {
            min_len = min(min_len, r - l + 1);
            sum -= nums[l++];
        }
        return min_len > nums.size() ? 0 : min_len;
    }
};
