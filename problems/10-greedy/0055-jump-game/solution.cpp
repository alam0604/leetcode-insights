// 55. Jump Game  [Medium]
// https://leetcode.com/problems/jump-game/
// Accepted 2021-09-04 · Runtime 60 ms · Memory 48.5 MB

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n);
        dp[n - 1] = true;
        int pos = n - 1;
        for(int i = n - 2; i >= 0; i--){
            int newPos = i + nums[i];
            if(newPos >= pos)
            {
                dp[i] = true;
                pos = i;
            }
            else
                dp[i] = false;
            
        }
        return dp[0];
    }
};
