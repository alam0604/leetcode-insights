// 312. Burst Balloons  [Hard]
// https://leetcode.com/problems/burst-balloons/
// Accepted 2022-08-01 · Runtime 451 ms · Memory 8.3 MB

class Solution {
public:
    int dp[301][301];
    int maxCoins(vector<int>& nums) {
        
        memset(dp, -1, sizeof dp);
        return fun(nums, 0, nums.size() - 1);
    }
    
    int fun(vector<int> &nums, int i, int j) {
        if(i > j) return 0;
        if(dp[i][j] != -1) return dp[i][j];
        
        int mx = INT_MIN;
        for(int k = i; k <= j; k++) {
            
            int x = fun(nums, i, k - 1);
            int y = fun(nums, k + 1, j);
            
            int l = (i - 1 >= 0 ? nums[i - 1] : 1);
            int r = (j + 1 <= nums.size() - 1 ? nums[j + 1] : 1);
            
            mx = max(mx, x + y + l * r * nums[k]);
        }
        return dp[i][j] = mx;
    }
};
