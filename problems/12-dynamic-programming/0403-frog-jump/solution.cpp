// 403. Frog Jump  [Hard]
// https://leetcode.com/problems/frog-jump/
// Accepted 2026-05-22 · Runtime 60 ms · Memory 41.7 MB

class Solution {
public:
    unordered_map<int, int> mp;
    int dp[2005][2005];
    bool canCross(vector<int>& s) {
        memset(dp, -1, sizeof dp);
        for(int i = 1; i < s.size(); i++) mp[s[i]] = i;
        if(s[1] != 1) return 0;
        return fun(s, 1, 1);
    }

    int fun(vector<int> &s, int i, int k) {
        if(i >= s.size() or i <= 0) return 0;
        if(i == s.size() - 1) return 1;
        if(dp[i][k] != -1) return dp[i][k];
        int f = 0;
        for(int jump = -1; jump <= 1; jump += 1) {
            int val = s[i] + (k + jump);
            int new_k = k + jump;
            if(mp[val] and new_k != 0) {
                f |= fun(s, mp[val], new_k);
                if(f) return f;
            }
        }
        return dp[i][k] = f;
    }

};
