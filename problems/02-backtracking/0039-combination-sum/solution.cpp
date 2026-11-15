// 39. Combination Sum  [Medium]
// https://leetcode.com/problems/combination-sum/
// Accepted 2022-01-16 · Runtime 172 ms · Memory 75.9 MB

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> v;
        int n = candidates.size();
        fun(res, v, candidates, target, n);
        return res;
    }
    
    void fun(vector<vector<int>> &res, vector<int> v, vector<int>& candidates, int                  target, int n) {
        
        
        if(target == 0) {
            res.push_back(v);
            return;
        }
        if(n <= 0) return;
        
        if(candidates[n - 1] <= target) {
            fun(res, v, candidates, target, n - 1);
            v.push_back(candidates[n - 1]);
            fun(res, v, candidates, target - candidates[n - 1], n);
        }
        else fun(res, v, candidates, target, n - 1);
    }
};
