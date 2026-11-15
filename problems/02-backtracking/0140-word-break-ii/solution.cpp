// 140. Word Break II  [Hard]
// https://leetcode.com/problems/word-break-ii/
// Accepted 2022-08-16 · Runtime 7 ms · Memory 7.7 MB

class Solution {
public:
    map<string, vector<string>> memo;
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        
        map<string, int> mp;
        for(auto x : wordDict) mp[x]++;
        
        return fun(s, s.size(), mp);
    }
    
    vector<string> fun(string s, int n, map<string, int> &mp) {
        
        if(s.size() == 0) return {""};
        
        vector<string> temp;
        for(int i = 0; i <= s.size(); i++) {
            string t = getStr(s, i);
            if(mp[t]) {
                string ss = s.substr(i + 1);
                vector<string> dummy = fun(ss, n - i - 1, mp);
                
                for(auto x : dummy) {
                    temp.push_back(t + ' ' + x);
                    // remove spaces if present at the end
                    if(x.size() == 0) 
                        temp.back().pop_back();
                }
            }
        }
        return memo[s] = temp;
    }
    
    string getStr(string &s, int j) {
        string out = "";
        for(int i = 0; i <= j; i++) 
            out.push_back(s[i]);
        return out;
    }
};
