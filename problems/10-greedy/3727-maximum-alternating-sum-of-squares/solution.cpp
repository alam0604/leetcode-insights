class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long ans = 0;
        for(auto &x : nums) if(x < 1) x *= -1;
        sort(nums.begin(), nums.end()); int l = 0, h = nums.size() - 1;
        while(l <= h) {
            ans += (long)nums[h] * (long)nums[h];
            if(l == h) break;
            ans -= (long)nums[l] * (long)nums[l];
            l++, h--;
        }
        return ans;
    }
};
