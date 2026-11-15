// 131. Palindrome Partitioning  [Medium]
// https://leetcode.com/problems/palindrome-partitioning/
// Accepted 2022-08-01 · Runtime 163 ms · Memory 75.7 MB

class Solution {
public:
    vector<vector<string>> res;
    vector<vector<string>> partition(string s) {
        vector<string> dummy;
        fun(s, 0, dummy);
        return res;
    }
    
    void fun(string &s, int start, vector<string> &dummy) {
        if(start == s.size()) {
            res.push_back(dummy);
            return;
        }
        
        for(int i = start; i < s.size(); i++) {
            if(isPalin(s, start, i)) {
                string temp = getString(s, start, i);
                dummy.push_back(temp);
                fun(s, i + 1, dummy);
                dummy.pop_back();
            }
        }
    }
    
    string getString(string &s, int i, int j) {
        string out = "";
        for(; i <= j; i++) out.push_back(s[i]);
        return out;
    }
    
    int isPalin(string &s, int i, int j) {
        while(i < j) {
            if(s[i++] != s[j--]) return 0;
        }
        return 1;
    }
};
