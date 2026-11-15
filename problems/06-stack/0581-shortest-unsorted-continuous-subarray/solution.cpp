// 581. Shortest Unsorted Continuous Subarray  [Medium]
// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
// Accepted 2022-05-03 · Runtime 43 ms · Memory 27.4 MB

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        
        int n = nums.size();
        vector<int> d = nums;
        sort(d.begin(), d.end());
        
        int l = 0, r = n - 1;
        while(l < n and nums[l] == d[l])
            l++;
        if(l == n) return 0;
        while(r >= 0 and nums[r] == d[r])
            r--;
        return r - l + 1;
    }
};
