// 78. Subsets  [Medium]
// https://leetcode.com/problems/subsets/
// Accepted 2022-02-13 · Runtime 4 ms · Memory 10.9 MB

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        vector<int> dummy;
        
        fun(nums, res, dummy, n);
        return res;
    }
    
    void fun(vector<int> &nums, vector<vector<int>> &res, vector<int> &dummy, int n) {
        if(n == 0) {
            res.push_back(dummy);
            return;
        }
        
        fun(nums, res, dummy, n - 1);
        dummy.push_back(nums[n - 1]);
        fun(nums, res, dummy, n - 1);
        dummy.pop_back();
    }
};
