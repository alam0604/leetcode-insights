// 137. Single Number II  [Medium]
// https://leetcode.com/problems/single-number-ii/
// Accepted 2026-11-16 · Runtime 2 ms · Memory 16.1 MB
// Approach: count set bits per position in a 32-slot array, keep bits whose count % 3 != 0

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res[32]; memset(res, 0, sizeof res);
        for(int i = 0; i < 32; i++) {
            for(auto x : nums)
                res[i] += (x & (1 << i) ? 1 : 0);
        }
        int val = 0;
        for(int i = 0; i < 32; i++)
            if(res[i] % 3 != 0) val |= (1 << i);
        return val;
    }
};
