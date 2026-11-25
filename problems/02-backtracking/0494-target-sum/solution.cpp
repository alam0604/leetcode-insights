class Solution {
public:
    int dp[2002][21];
    int findTargetSumWays(vector<int>& nums, int target) {
        memset(dp, -1, sizeof dp);
        return fun(nums, 0, 0, target);
    }
    int fun(vector<int> &nums, int sum, int i, int &target) {
        if(i == nums.size()) return target == sum;
        if(dp[(sum + 1000)][i] != -1) return dp[(sum + 1000)][i];
        int a = fun(nums, sum + nums[i], i + 1, target);
        int b = fun(nums, sum - nums[i], i + 1, target);
        return dp[(sum + 1000)][i] = a + b;
    }
};
