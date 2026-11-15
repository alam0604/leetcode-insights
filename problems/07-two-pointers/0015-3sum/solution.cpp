// 15. 3Sum  [Medium]
// https://leetcode.com/problems/3sum/
// Accepted 2024-04-10 · Runtime 59 ms · Memory 27.2 MB

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      vector<vector<int>> res;
      sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); i++) {
          if(i > 0 and nums[i] == nums[i - 1]) continue;
          int l = i + 1, h = nums.size() - 1;
          while(l < h) {
            int sum = nums[i] + nums[l] + nums[h];
            if(sum == 0) {
              res.push_back({nums[i], nums[l], nums[h]});
              l += 1, h -= 1;
              while(l < h and nums[l] == nums[l - 1]) l += 1;
              while(l < h and nums[h] == nums[h + 1]) h -= 1;
            }
            else if(sum < 0) l += 1;
            else h -= 1;
          }
        }
        return res;
    }
};
