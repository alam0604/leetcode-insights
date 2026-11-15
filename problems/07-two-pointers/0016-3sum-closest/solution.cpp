// 16. 3Sum Closest  [Medium]
// https://leetcode.com/problems/3sum-closest/
// Accepted 2022-10-08 · Runtime 464 ms · Memory 16.4 MB

class Solution {
public:
    int threeSumClosest(vector<int>& a, int target) {
        int n = a.size();
        sort(a.begin(), a.end());
        
        long long closest = INT_MAX;
        for(int i = 0; i < n; i++) {
            int l = i + 1, h = n - 1;
            while(l < h) {
                int s = a[i] + a[l] + a[h];
                if(s == target) return s;
                if(abs(s - target) < abs(closest - target))
                    closest = s;
                if(s < target) l++;
                else h--;
            }
        }
        return closest;
    }
};
