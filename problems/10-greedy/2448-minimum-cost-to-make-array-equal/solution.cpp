// 2448. Minimum Cost to Make Array Equal  [Hard]
// https://leetcode.com/problems/minimum-cost-to-make-array-equal/
// Accepted 2023-06-21 · Runtime 1921 ms · Memory 363.2 MB

#define vc vector
class Solution {
public:
    long long getVal(vc<vc<long long>> &v, int m) {
        long long sum = 0;
        for(auto x : v)
            sum += abs(x[0] - m) * x[1];
        return sum;
    }
    long long minCost(vector<int>& nums, vector<int>& cost) {
        vc<vc<long long>> v;
        for(int i = 0; i < nums.size(); i++)
            v.push_back({(long long)nums[i], (long long)cost[i]});
        sort(v.begin(), v.end());
        int l = 0, h = v.back()[0]; long long res = 0;
        while(l <= h) {
            int m = l + (h - l) / 2;
            if(getVal(v, m) < getVal(v, m + 1)) {
                res = getVal(v, m);
                h = m - 1;
            }
            else
                l = m + 1;
        }
        return res;
    }
};
