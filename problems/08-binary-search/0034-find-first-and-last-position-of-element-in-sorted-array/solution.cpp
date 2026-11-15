// 34. Find First and Last Position of Element in Sorted Array  [Medium]
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// Accepted 2022-10-01 · Runtime 19 ms · Memory 13.6 MB

class Solution {
public:
    
    int firstIndex(vector<int>& nums, int l, int h, int target) {
        int ans = -1;
        while(l <= h) {
            int m = l + (h - l) / 2;
            if(nums[m] == target) {
                ans = m;
                h = m - 1;
            }
            else if(nums[m] < target) l = m + 1;
            else h = m - 1;
        }
        return ans;
    }
    
    int lastIndex(vector<int>& nums, int l, int h, int target) {
        int ans = -1;
        while(l <= h) {
            int m = l + (h - l) / 2;
            if(nums[m] == target) {
                ans = m;
                l = m + 1;
            }
            else if(nums[m] < target) l = m + 1;
            else h = m - 1;
        }
        return ans;
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        int a = firstIndex(nums, 0, nums.size() - 1, target);
        int b = lastIndex(nums, 0, nums.size() - 1, target);
        res.push_back(a); res.push_back(b);
        return res;
    }
};
