// 5. Longest Palindromic Substring  [Medium]
// https://leetcode.com/problems/longest-palindromic-substring/
// Accepted 2026-11-12 · Runtime 142 ms · Memory 165 MB

class Solution {
public:
    
    int start = 0, length = 0;
    string longestPalindrome(string s) {
        
        
        int n = s.size();
        
        for(int i = 0; i < n; i++) {
            checkPalin(s, i, i);
            checkPalin(s, i, i + 1);
        }
        
        
        cout << start << " " << length;
        
        string out = "";
        for(int i = start; i < start + length; i++)
            out += s[i];
        return out;
        
    }
    
    void checkPalin(string s, int l, int h) {
        
        while(l >= 0 and h < s.size() and s[l] == s[h])
            l--, h++;
        
        int size = h - l - 1;
        if(size > length) {
            length = size;
            start = l + 1;
        }
    }
};
