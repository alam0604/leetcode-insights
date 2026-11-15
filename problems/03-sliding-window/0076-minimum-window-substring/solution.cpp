// 76. Minimum Window Substring  [Hard]
// https://leetcode.com/problems/minimum-window-substring/
// Accepted 2022-10-22 · Runtime 360 ms · Memory 8.3 MB

class Solution {
public:
    int check(vector<int> &curr, vector<int> &pat) {
        for(int i = 0; i < 256; i++) {
            if(pat[i] > curr[i]) return 0;
        }
        return 1;
    }
    string minWindow(string s, string t) {
        vector<int> pat(256, 0), curr(256, 0);
        int i = 0, j = 0, start = 0, min_len = INT_MAX;
        
        for(auto x : t)
            pat[x]++;
        
        while(j < s.size()) {
            curr[s[j++]]++;
            while(check(curr, pat)) {
                
                int len = j - i;
                if(len < min_len) {
                    start = i;
                    min_len = len;
                }
                curr[s[i++]]--;
            }
        }
        while(check(curr, pat)) {
            int len = j - i;
            if(len < min_len) {
                start = i;
                min_len = len;
            }
            curr[s[i++]]--;
        }
        
        string out = "";
        if(min_len != INT_MAX) {
            for(int i = start; i < start + min_len; i++)
                out.push_back(s[i]);
        }
        return out;
    }
};
