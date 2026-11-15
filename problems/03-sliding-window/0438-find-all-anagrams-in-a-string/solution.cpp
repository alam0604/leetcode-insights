// 438. Find All Anagrams in a String  [Medium]
// https://leetcode.com/problems/find-all-anagrams-in-a-string/
// Accepted 2022-02-19 · Runtime 29 ms · Memory 8.7 MB

class Solution {
public:
    
    bool compare(vector<int> &a, vector<int> &b) {
        return a == b;
    }
    
    vector<int> findAnagrams(string s, string p) {
        vector<int> mp1(26, 0), mp2(26, 0), res;
        for(auto ch : p) mp1[ch - 'a'] += 1;
        
        int i = 0, j = 0;
        while(j < s.size()) {
            mp2[s[j] - 'a'] += 1;
            if(j - i + 1 < p.size()) {
                j++;
                continue;
            }
            
            if(compare(mp1, mp2)) res.push_back(i);
            mp2[s[i] - 'a'] -= 1;
            i++, j++;
        }
        return res;
    }
};
