// 137. Single Number II  [Medium]
// https://leetcode.com/problems/single-number-ii/
// Accepted 2026-11-16 · Runtime 1 ms · Memory 16.1 MB
// Approach: for each bit position, count set bits with one counter; keep the bit if count % 3 != 0

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int i = 0; i < 32; i++) {
            int bits = 0;
            for(auto x : nums)
                bits += (x & (1 << i) ? 1 : 0);  
            if(bits % 3 != 0) res |= (1 << i);
        }
        return res;
    }
};
