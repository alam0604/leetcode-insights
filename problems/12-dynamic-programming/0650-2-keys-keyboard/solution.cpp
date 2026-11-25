class Solution {
public:
    
    int dp[1005];
    int minSteps(int n) {
        memset(dp, -1, sizeof dp);
        return fun(n);
    }
    
    int fun(int n) {
        if(n == 0 or n == 1) return 0;
        if(n == 2 or n == 3) return n;
        if(dp[n] != -1) return dp[n];
        int f = isPrime(n);
        if(f) return n;
        
        int ans = INT_MAX;
        for(int i = 2; i * i <= n; i++) {
            if(n % i == 0) {
                int f1 = i, f2 = n / i;
                int val = fun(f1) + fun(f2);
                ans = min(ans, val);
            }
        }
        return dp[n] = ans;
    }
    
    int isPrime(int n) {
        if(n == 2) return 1;
        for(int i = 2; i * i <= n; i++)
            if(n % i == 0) return 0;
        return 1;
    }
};
