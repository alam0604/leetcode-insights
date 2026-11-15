// 540. Single Element in a Sorted Array  [Medium]
// https://leetcode.com/problems/single-element-in-a-sorted-array/
// Accepted 2022-04-11 · Runtime 72 ms · Memory 22.4 MB

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        int l = 0, h = nums.size() - 1;
        while(l <= h) {
            int m = l + (h - l) / 2;
            
            if(m == 0) return nums[m];
            if(nums[m] == nums[m - 1]) {
                if(m & 1) l = m + 1;
                else h = m - 2;
            }
            else if(nums[m] == nums[m + 1]) {
                if(m & 1) h = m - 1;
                else l = m + 2;
            }
            else return nums[m];
        }
        return nums[0];
    }
};
