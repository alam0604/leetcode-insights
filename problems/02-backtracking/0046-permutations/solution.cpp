// 46. Permutations  [Medium]
// https://leetcode.com/problems/permutations/
// Accepted 2022-04-22 · Runtime 0 ms · Memory 7.6 MB

class Solution {
public:
    void fun(vector<int> &nums, int s, vector<vector<int>> &res) {
        if(s >= nums.size()) {
            res.push_back(nums);
            return;
        }
        
        for(int i = s; i < nums.size(); i++) {
            swap(nums[i], nums[s]);
            fun(nums, s + 1, res);
            swap(nums[i], nums[s]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        fun(nums, 0, res);
        return res;
    }
};
