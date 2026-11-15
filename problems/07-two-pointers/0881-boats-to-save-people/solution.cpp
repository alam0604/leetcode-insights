// 881. Boats to Save People  [Medium]
// https://leetcode.com/problems/boats-to-save-people/
// Accepted 2022-03-24 · Runtime 76 ms · Memory 41.9 MB

class Solution {
public:
    int numRescueBoats(vector<int>& p, int limit) {
        int n = p.size();
        sort(p.begin(), p.end());
        int cnt = 0, i = 0, j = n - 1;
        while(i < j) {
            int x = p[i] + p[j];
            if(x > limit) {cnt++; j--;}
            else if(x <= limit) {cnt++; i++, j--;}
        }
        if(i == j) cnt++;
        return cnt;
    }
};
