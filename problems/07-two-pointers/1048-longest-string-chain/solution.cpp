// 1048. Longest String Chain  [Medium]
// https://leetcode.com/problems/longest-string-chain/
// Accepted 2022-06-15 · Runtime 241 ms · Memory 55.8 MB

class Solution {
public:
    
    static bool comp(string &a, string &b) {
        return a.size() < b.size();
    }
    
    unordered_map<string, int> dp, mp;
    
    int longestStrChain(vector<string>& words) {
        
        sort(words.begin(), words.end(), comp);
        for(auto x : words) mp[x]++;
        
        int ans = 0;
        for(auto x : words) {
            mp[x]--;
            int count = fun(x);
            mp[x]++;
            ans = max(ans, count);
        }
        
        return ans;
    }
    
    int fun(string &s) {
        
        if(s.size() == 1) return 1;
        
        if(dp[s] > 0) return dp[s];
        
        int ans = 0;
        for(int i = 0; i < s.size(); i++) {
            string x = getString(s, i);
            
            if(mp[x] > 0) {
                mp[x]--;
                int val = fun(x);
                mp[x]++;
                
                ans = max(ans, val);
            }
        }
        
        return dp[s] = ans + 1;
    }
    
    string getString(string &s, int i) {
        string x = "";
        for(int j = 0; j < s.size(); j++) {
            if(i == j) continue;
            x += s[j];
        }
        return x;
    }
};
