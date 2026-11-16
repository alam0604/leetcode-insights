class Solution {
public:
    int climbStairs(int n, vector<int>& ct) {
        vector<int> res(n, 0);
        res[n - 1] = 0;
        for(int i = n - 2; i >= 0; i--) {
            int a, b, c; a = b = c = INT_MAX;
            if(i + 1 < n)
                a = ct[i + 1] + 1 + res[i + 1];
            if (i + 2 < n)
                b = ct[i + 2] + 4 + res[i + 2];
            if(i + 3 < n)
                c = ct[i + 3] + 9 + res[i + 3];
            res[i] = min(a, min(b, c));
        }
        if(n == 1) return ct[0] + 1;
        if(n == 2) return min(res[0] + ct[0] + 1, res[1] + ct[1] + 4);
        return min(res[0] + 1 + ct[0], min(res[1] + 4 + ct[1], res[2] + 9 + ct[2]));
    }
};
