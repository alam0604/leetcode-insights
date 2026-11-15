// 33. Search in Rotated Sorted Array  [Medium]
// https://leetcode.com/problems/search-in-rotated-sorted-array/
// Accepted 2022-04-22 · Runtime 3 ms · Memory 11.1 MB

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        
        while(l <= r) {
            int m = l + (r - l) / 2;
            if(nums[m] == target) return m;
            if(nums[l] == nums[r]) l++, r--;
            else if(nums[l] <= nums[m]) {
                if(target >= nums[l] and target < nums[m]) r = m - 1;
                else l = m + 1;
            }
            else {
                if(target > nums[m] and target <= nums[r]) l = m + 1;
                else r = m - 1;
            }
        }
        return -1;
    }
};
