// 354. Russian Doll Envelopes  [Hard]
// https://leetcode.com/problems/russian-doll-envelopes/
// Accepted 2026-05-03 · Runtime 152 ms · Memory 107 MB

class Solution {
public:
    static inline bool comp(vector<int> &x, vector<int> &y) {
        if(x[0] == y[0])
            return x[1] > y[1];
        return x[0] < y[0];
    }
    int maxEnvelopes(vector<vector<int>>& en) {
        sort(en.begin(), en.end(), comp);
        
        set<int> s;
        for(auto x : en) {
            auto p = s.lower_bound(x[1]);
            if(p == s.end())
                s.insert(x[1]);
            else if(x[1] < *p) {
                s.erase(*p);
                s.insert(x[1]);
            }
        }
        return s.size();
    }
};
