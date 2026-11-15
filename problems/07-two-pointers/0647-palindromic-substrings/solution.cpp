// 647. Palindromic Substrings  [Medium]
// https://leetcode.com/problems/palindromic-substrings/
// Accepted 2022-05-22 · Runtime 20 ms · Memory 10.7 MB

class Solution {
public:
    int countSubstrings(string s) {
        
        int n = s.size();
        int dp[n + 1][n + 1];
        memset(dp, 0, sizeof dp);
        
        for(int i = 0; i <= n; i++) dp[0][i] = dp[1][i] = 1;
        
        for(int i = 2; i <= n; i++) {
            for(int j = i; j <= n; j++) {
                if(s[j - 1] == s[j - i]) {
                    if(dp[i - 2][j - 1])
                        dp[i][j] = 1;
                }
            }
        }
        
        int res = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++)
                res += dp[i][j];
        }
        return res;
    }
};
