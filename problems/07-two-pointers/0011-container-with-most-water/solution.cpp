// 11. Container With Most Water  [Medium]
// https://leetcode.com/problems/container-with-most-water/
// Accepted 2022-06-04 · Runtime 112 ms · Memory 59.1 MB

class Solution {
public:
    int maxArea(vector<int>& h) {
        
        int i = 0, j = h.size() - 1;
        int mx = 0;
        
        while(i < j) {
            int mx_water = (j - i) * min(h[i], h[j]);
            mx = max(mx, mx_water);
            if(h[i] < h[j]) i++;
            else j--;
        }
        return mx;
    }
};
