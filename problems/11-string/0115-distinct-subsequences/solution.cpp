// 115. Distinct Subsequences  [Hard]
// https://leetcode.com/problems/distinct-subsequences/
// Accepted 2022-08-18 · Runtime 40 ms · Memory 10.9 MB

class Solution {
public:
    int dp[1001][1001];
    int numDistinct(string s, string t) {
        
        memset(dp, -1, sizeof dp);
        return fun(s, s.size(), t, t.size());
    }
    
    int fun(string &s, int n, string &t, int m) {
        if(m == 0 and n == 0) return 1;
        if(m == 0) return 1;
        if(n == 0) return 0;
        
        if(dp[n][m] != -1) return dp[n][m];
        
        if(s[n - 1] == t[m - 1]) {
            int x = fun(s, n - 1, t, m - 1);
            int y = fun(s, n - 1, t, m);
            
            return dp[n][m] = x + y;
        }
        else
            return dp[n][m] = fun(s, n - 1, t, m);
    }
};
