// 72. Edit Distance  [Medium]
// https://leetcode.com/problems/edit-distance/
// Accepted 2024-03-27 · Runtime 44 ms · Memory 10.2 MB

class Solution {
public:
    int dp[501][501];
    int minDistance(string s, string t) {
        memset(dp, -1, sizeof dp);
        return fun(s, t, 0, 0);
    }
    
    int fun(string &s, string &t, int i, int j) {
        if(i >= s.size()) return t.size() - j;
        if(j >= t.size()) return s.size() - i;
        if(dp[i][j] != -1) return dp[i][j];
        if(s[i] == t[j]) return dp[i][j] = fun(s, t, i + 1, j + 1);
        else {
            int inserted = fun(s, t, i + 1, j);
            int deleted = fun(s, t, i, j + 1);
            int replaced = fun(s, t, i + 1, j + 1);
            return dp[i][j] = min({inserted, deleted, replaced}) + 1;
        }
        return 0;
    }
};
