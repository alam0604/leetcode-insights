// 90. Subsets II  [Medium]
// https://leetcode.com/problems/subsets-ii/
// Accepted 2022-02-13 · Runtime 18 ms · Memory 13.7 MB

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        unordered_map<string, int> mp;
        vector<vector<int>> res;
        vector<int> dummy;
        
        fun(nums, res, mp, dummy, nums.size());
        return res;
    }
    
    void fun(vector<int> &nums, vector<vector<int>> &res, unordered_map<string, int> &mp, vector<int> &dummy, int n) {
        if(n <= 0) {
            string out = "";
            for(auto &x : dummy) out += to_string(x) + "*";
            sort(out.begin(), out.end());
            if(mp[out] == 0) {
                res.push_back(dummy);
                mp[out]++;
            }
            return;
        }
        
        fun(nums, res, mp, dummy, n - 1);
        dummy.push_back(nums[n - 1]);
        fun(nums, res, mp, dummy, n - 1);
        dummy.pop_back();
    }
};
