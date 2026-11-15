// 139. Word Break  [Medium]
// https://leetcode.com/problems/word-break/
// Accepted 2022-08-16 · Runtime 79 ms · Memory 26 MB

class Solution {
public:
    int dp[301];
    bool wordBreak(string s, vector<string>& wordDict) {
        
        memset(dp, -1, sizeof dp);
        map<string, bool> mp;
        for(auto x : wordDict) mp[x] = true;
        return mcm(s, 0, s.size(), mp);
    }
    
    bool mcm(string s, int i, int n, map<string, bool> &mp) {
        
        if(s.size() == 0) return true;
        if(dp[n] != -1) return dp[n];
        
        
        // cout << s << "\n";
        for(int k = 0; k < s.size(); k++) {
            string t = getStr(s, k);
            // cout << t << " | ";
            if(mp[t]) {
                
                string ss = s.substr(k + 1);
                // cout << "\n" << t << " : " << ss << endl;
                bool f = mcm(ss, k + 1, n - k - 1, mp);
                if(f) return dp[n] = 1;
            }
        }
        return dp[n] = 0;
    }
    
    string getStr(string &s, int j) {
        string out = "";
        for(int i = 0; i <= j; i++) out.push_back(s[i]);
        return out;
    }
};
