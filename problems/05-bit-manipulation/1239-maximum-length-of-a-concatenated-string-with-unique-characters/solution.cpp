// 1239. Maximum Length of a Concatenated String with Unique Characters  [Medium]
// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
// Accepted 2022-10-24 · Runtime 10 ms · Memory 8.2 MB

class Solution {
public:
    int mx;
    int maxLength(vector<string>& arr) {
        mx = 0;
        vector<int> mp(26, 0);
        fun(arr, 0, 0, mp);
        return mx;
    }
    
    void fun(vector<string> &arr, int i, int curr_mx, vector<int> &mp) {
        
        if(i == arr.size()) {
            mx = max(mx, curr_mx);
            return;
        }
        
        int f = 1;
        
        for(auto ch : arr[i]) {
            if(mp[ch - 'a']) f = 0;
            mp[ch - 'a']++;
        }
        
        if(f)
            fun(arr, i + 1, curr_mx + arr[i].size(), mp);
        for(auto ch : arr[i])
            mp[ch - 'a']--;
        fun(arr, i + 1, curr_mx, mp);
    }
};
