class Solution {
public:
    vector<int> successfulPairs(vector<int>& s, vector<int>& p, long long success) {
        vector<int> res; sort(p.begin(), p.end());
        for(auto x : s) {
            int l = 0, h = p.size() - 1;
            while(l < h) {
                int m = l + (h - l) / 2;
                if((long)x * (long)p[m] >= success)
                    h = m;
                else
                    l = m + 1;
            }
            if(((long)p[h] * (long)x) < success) res.push_back(0);
            else res.push_back(p.size() - h);
        }
        return res;
    }
};
