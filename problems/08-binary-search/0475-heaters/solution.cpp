class Solution {
public:
    int findRadius(vector<int>& hs, vector<int>& ht) {
        sort(ht.begin(), ht.end()); int mx = 0;
        for(auto x : hs) {
            int mn = INT_MAX;
            auto idx = lower_bound(ht.begin(), ht.end(), x);
            if(idx != ht.end() and *idx == x) continue;
            int pos = idx - ht.begin();
            if(pos == ht.size()) mn = abs(x - ht.back());
            else if(pos < ht.size()) mn = min(mn, abs(x - ht[pos]));
            if(pos - 1 >= 0) mn = min(mn, abs(x - ht[pos - 1]));
            mx = max(mx, mn);
        }
        return mx;
    }
};
