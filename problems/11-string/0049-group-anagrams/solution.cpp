// 49. Group Anagrams  [Medium]
// https://leetcode.com/problems/group-anagrams/
// Accepted 2022-10-28 · Runtime 37 ms · Memory 22.9 MB

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> mp;
        
        for(auto x : strs) {
            string s = x;
            sort(s.begin(), s.end());     
            mp[s].push_back(x);
        }
        
        for(auto x : mp) {
            vector<string> p = x.second;
            
            vector<string> ans;
            for(auto y : p)
                ans.push_back(y);
            res.push_back(ans);
        }
        return res;
      }
};
