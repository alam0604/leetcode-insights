// 42. Trapping Rain Water  [Hard]
// https://leetcode.com/problems/trapping-rain-water/
// Accepted 2022-09-18 · Runtime 38 ms · Memory 19.7 MB

class Solution {
public:
    int trap(vector<int>& v) {
        
        int i = 0, j = v.size() - 1;
        int l = v[0], r = v[j];
        
        int water = 0;
        while(i < j) {
            
            if(r > l) {
                while(v[i] <= l and i < j) {
                    water += l - v[i];
                    i += 1;
                }
                
                if(i < j and v[i] >= l) l = v[i];
            }
            else {
                while(v[j] <= r and i < j) {
                    water += r - v[j];
                    j -= 1;
                }
                
                if(i < j and v[j] >= r) r = v[j];
            }
        }
        return water;
    }
};
