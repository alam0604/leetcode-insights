// 260. Single Number III  [Medium]
// https://leetcode.com/problems/single-number-iii/
// Accepted 2026-11-16 · Runtime 0 ms · Memory 13.6 MB

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int xor_val = 0;
        for(auto x : nums) xor_val ^= x;
        int i = 0;
        for(; i < 32; i++)
            if(xor_val & (1 << i)) break;
        
        // cout << xor_val << " " << (1 << i) << endl;
        int num1 = 0, num2 = 0;
        for(auto x : nums) {
            if(x & (1 << i)) num1 ^= x;
            else num2 ^= x;
        }
        return {num1, num2};
    }
};
