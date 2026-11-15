// 174. Dungeon Game  [Hard]
// https://leetcode.com/problems/dungeon-game/
// Accepted 2022-05-09 · Runtime 12 ms · Memory 8.8 MB

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dune) {
        int n = dune.size();
        int m = dune[0].size();
        
        int dp[n][m];
        memset(dp, 0, sizeof dp);
        if(dune[n - 1][m - 1] < 0)
            dp[n - 1][m - 1] = 1 - dune[n - 1][m - 1];
        else dp[n - 1][m - 1] = 1;
        
        
        for(int j = m - 2; j >= 0; j--) {
            if(dune[n - 1][j] > 0)
                dp[n - 1][j] = max(1, dp[n - 1][j + 1] - dune[n - 1][j]);
            else dp[n - 1][j] = abs(dune[n - 1][j] - dp[n - 1][j + 1]);
        }
        
        for(int i = n - 2; i >= 0; i--) {
            if(dune[i][m - 1] > 0)
                dp[i][m - 1] = max(1, dp[i + 1][m - 1] - dune[i][m - 1]);
            else
                dp[i][m - 1] = abs(dune[i][m - 1] - dp[i + 1][m - 1]);
        }
        
        for(int i = n - 2; i >= 0; i--) {
            for(int j = m - 2; j >= 0; j--) {
                if(dune[i][j] < 0) {
                    int x = dp[i + 1][j];
                    int y = dp[i][j + 1];
                    
                    dp[i][j] = abs(dune[i][j] - min(x, y));
                }
                else {
                    int x = min(dp[i + 1][j], dp[i][j + 1]);
                    dp[i][j] = max(1, x - dune[i][j]);
                }   
            }
        }
        
        
        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j < m; j++)
        //         cout << dp[i][j] << " ";
        //     cout << endl;
        // }
        
        return dp[0][0];
    }
};
