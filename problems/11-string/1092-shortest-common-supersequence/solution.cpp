// 1092. Shortest Common Supersequence  [Hard]
// https://leetcode.com/problems/shortest-common-supersequence/
// Accepted 2022-08-12 · Runtime 31 ms · Memory 10.6 MB

class Solution {
public:
    int dp[1001][1001];
    string shortestCommonSupersequence(string s1, string s2) {
        memset(dp, 0, sizeof dp);
        
        for(int i = 1; i <= s1.size(); i++) {
            for(int j = 1; j <= s2.size(); j++) {
                if(s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        
        int x = s1.size(), y = s2.size();
        string out = "";
        while(x > 0 and y > 0) {
            if(s1[x - 1] == s2[y - 1]) {
                out.push_back(s1[x - 1]);
                x -= 1, y -= 1;
            }
            else {
                if(dp[x - 1][y] > dp[x][y - 1]) {
                    out.push_back(s1[x - 1]);
                    x -= 1;
                }
                else {
                    out.push_back(s2[y - 1]);
                    y -= 1;
                }
            }
        }
        while(x > 0) {
            out.push_back(s1[x - 1]); 
            x -= 1;
        }
        while(y > 0) {
            out.push_back(s2[y - 1]); 
            y -= 1;
        }
        reverse(out.begin(), out.end());
        return out;
    }
};
