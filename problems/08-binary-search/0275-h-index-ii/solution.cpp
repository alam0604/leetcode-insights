class Solution {
public:
    int hIndex(vector<int>& ct) {
        int l = 0, h = 1001, res = INT_MIN;
        while(l <= h) {
            int m = l + (h - l) / 2, flag = 0;
            for(auto x : ct)
                flag += (x >= m);
            if(flag >= m)
                res = m, l = m + 1;
            else h = m - 1;
        }
        return res;
    }
};
