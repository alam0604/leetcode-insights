// 239. Sliding Window Maximum  [Hard]
// https://leetcode.com/problems/sliding-window-maximum/
// Accepted 2022-04-01 · Runtime 590 ms · Memory 189.7 MB

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& v, int k) {
        int n = v.size();
        vector<int> res;
        if(k == 1) return v;
        int j = 0, i = 0, mx = INT_MIN;
        list<int> l;
        while (j < n) {
            while (l.size() > 0 and v[j] > l.back())
                l.pop_back();
            l.push_back(v[j]);
            mx = max(mx, v[j]);
            if (j - i + 1 < k)
                j++;
            else {
                res.push_back(mx);
                if (v[i] == mx) {
                    l.pop_front();
                    mx = max(l.front(), l.back());
                }
                i++, j++;
            }
        }
        return res;
    }
};
