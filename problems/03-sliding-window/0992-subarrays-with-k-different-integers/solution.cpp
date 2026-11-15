// 992. Subarrays with K Different Integers  [Hard]
// https://leetcode.com/problems/subarrays-with-k-different-integers/
// Accepted 2022-02-26 · Runtime 160 ms · Memory 45.2 MB

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int x = fun(nums, k);
        int y = fun(nums, k - 1);
        cout << x << " " << y << endl;
        return x - y;
    }
    
    int fun(vector<int> &v, int k) {
        unordered_map<int, int> mp;
        int i = 0, j = 0, cnt = 0;
        while(j < v.size()) {
            mp[v[j]]++;
            if(mp[v[j]] == 1) k--;
            while(k < 0) {
                mp[v[i]]--;
                if(!mp[v[i]]) k++;
                i++;
            }
            cnt += j - i + 1;
            j++;
        }
        return cnt;
    }
};
