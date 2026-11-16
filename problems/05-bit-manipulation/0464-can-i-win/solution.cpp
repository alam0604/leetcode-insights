class Solution {
public:
    int dp[(1 << 21)][2];
    bool canIWin(int maxint, int dt) {
        memset(dp, -1, sizeof dp);
        if(((maxint) * (maxint + 1)) / 2 < dt) return 0;
        if(not dt) return 1;
        return fun(0, 0, maxint, dt, 0);
    }
    //
    int fun(int mask, int score, int num, int dt, int f) {
        if(dp[mask][f] != -1) return dp[mask][f];
        for(int i = 1; i <= num; i++) {
            int tmask = (1 << i);
            if(!(mask & tmask)) {
                int won = (score + i >= dt);
                won |= fun(mask | tmask, score + i, num, dt, f ^ 1) == 0;
                if(won) return dp[mask][f] = 1;
            }
        }
        return dp[mask][f] = 0;
    }
};
