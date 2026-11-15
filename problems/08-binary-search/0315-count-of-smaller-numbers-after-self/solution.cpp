// 315. Count of Smaller Numbers After Self  [Hard]
// https://leetcode.com/problems/count-of-smaller-numbers-after-self/
// Accepted 2022-07-23 · Runtime 162 ms · Memory 78.2 MB

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        
        int limitp = *max_element(nums.begin(), nums.end());
        int limitn = *min_element(nums.begin(), nums.end());
        
        int limit = max(limitp, abs(limitn)) + 1;
        vector<int> bit(2 * limit + 1, 0), res;
        
        for(int i = nums.size() - 1; i >= 0; i--)
            res.push_back(fun(bit, nums, nums[i] + limit, 2 * limit));
        
        reverse(res.begin(), res.end());
        return res;
    }
    
    int fun(vector<int> &bit, vector<int> &nums, int val, int limit) {
        
        int idx = val;
        for(; idx <= limit; idx += (idx & -idx))
            bit[idx]++;
        return sum(bit, val - 1);
    }
    
    int sum(vector<int> &bit, int x) {
        int sum = 0;
        for(; x > 0; x -= (x & -x))
            sum += bit[x];
        return sum;
    }
};
