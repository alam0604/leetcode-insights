// 75. Sort Colors  [Medium]
// https://leetcode.com/problems/sort-colors/
// Accepted 2024-04-02 · Runtime 0 ms · Memory 9.9 MB

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0, m = 0, h = nums.size() - 1;
        while(m <= h) {
          if(nums[m] == 0) {swap(nums[l], nums[m]); m++, l++;}
          else if(nums[m] == 1) m++;
          else {swap(nums[m], nums[h]); h--;}
        }
    }
};
