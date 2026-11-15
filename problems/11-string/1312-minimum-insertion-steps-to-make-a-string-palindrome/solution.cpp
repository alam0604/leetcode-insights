// 1312. Minimum Insertion Steps to Make a String Palindrome  [Hard]
// https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
// Accepted 2023-04-22 · Runtime 31 ms · Memory 7.6 MB

class Solution {
public:
    int dp[501][501];
    int minInsertions(string s) {
        memset(dp, -1, sizeof dp);
        return fun(s, 0, s.size() - 1);
    }

    int fun(string &s, int i, int j) {
        if(i > j) return 0;
        if(i == j) return 0;
        if(i + 1 == j) return s[i] != s[j];
        if(dp[i][j] != -1) return dp[i][j];
        if(s[i] == s[j])
            return dp[i][j] = fun(s, i + 1, j - 1);
        else {
            int x = fun(s, i + 1, j);
            int y = fun(s, i, j - 1);
            return dp[i][j] = min(x, y) + 1;
        }
    }
};
