// 567. Permutation in String  [Medium]
// https://leetcode.com/problems/permutation-in-string/
// Accepted 2022-01-11 · Runtime 8 ms · Memory 7.3 MB

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        
        int m = s1.size(), n = s2.size();
        if(m > n) return false;
        vector<int> mp1(26, 0), mp2(26, 0);
        
        for(auto x : s1) mp1[x - 'a']++;
        
        int i = 0, j = 0;
        while(j < n) {
            mp2[s2[j] - 'a']++;
            if(j - i + 1 < m) j++;
            else {
                if(mp1 == mp2) return true;
                mp2[s2[i] - 'a']--;
                i++, j++;
            }
        }
        return false;
    }
};
