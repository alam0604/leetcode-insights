class Solution {
public:
    int minFlips(int a, int b, int c) {
        int res = 0;
        while(a | b | c) {
            int is_set = (c & 1);
            int bits = (a & 1) + (b & 1);
            if(is_set and not bits) res += 1;
            if(not is_set and bits) res += bits;
            a >>= 1, b >>= 1, c >>= 1;
        }
        return res;
    }
};
