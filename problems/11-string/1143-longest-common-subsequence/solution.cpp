// 1143. Longest Common Subsequence  [Medium]
// https://leetcode.com/problems/longest-common-subsequence/
// Accepted 2022-12-15 · Runtime 38 ms · Memory 10.8 MB

class Solution {
public:
    
    int dp[1002][1001];
    
    int LCS(string &s1, int n, string &s2, int m) {
        if(m <= 0 or n <= 0) return 0;
        if(dp[n][m] != -1) return dp[n][m];
        if(s1[n - 1] == s2[m - 1])
            return dp[n][m] = 1 + LCS(s1, n - 1, s2, m - 1);
        
        int len1 = LCS(s1, n, s2, m - 1);
        int len2 = LCS(s1, n - 1, s2, m);
        return dp[n][m] = max(len1, len2);
    }
    
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        memset(dp, -1, sizeof dp);
        return LCS(text1, n, text2, m);
    }
};
