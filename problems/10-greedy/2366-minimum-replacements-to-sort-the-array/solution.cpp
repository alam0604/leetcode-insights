// 2366. Minimum Replacements to Sort the Array  [Hard]
// https://leetcode.com/problems/minimum-replacements-to-sort-the-array/
// Accepted 2022-08-06 · Runtime 152 ms · Memory 54.7 MB

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        
        long long ans = 0;
        
        int mn = nums.back();
        for(int i = nums.size() - 2; i >= 0; i--) {
            if(nums[i] == mn) continue;
            if(nums[i] > mn) {
                long long d = nums[i] / mn;
                if(nums[i] % mn != 0) d += 1;
                mn = nums[i] / d;
                
                ans += (d - 1);
            }
            else mn = nums[i];
        }
        return ans;
    }
};
