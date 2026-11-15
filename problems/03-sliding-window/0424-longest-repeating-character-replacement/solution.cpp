// 424. Longest Repeating Character Replacement  [Medium]
// https://leetcode.com/problems/longest-repeating-character-replacement/
// Accepted 2022-07-28 · Runtime 40 ms · Memory 6.9 MB

class Solution {
public:
    int characterReplacement(string s, int lim) {
        
        int mx_len = 1;
        for(char ch = 'A'; ch <= 'Z'; ch++) {
            int i = 0, j = 0, k = lim;
            while(j < s.size()) {
                if(s[j] == ch) j++;
                else {
                    if(k > 0) k--, j++;
                    else {
                        mx_len = max(mx_len, j - i);
                        while(k == 0) {
                            if(s[i] != ch) {
                                k++;
                                break;
                            }
                            i++;
                        }
                        i++;
                    }    
                }
            }
            mx_len = max(mx_len, j - i);
        }
        return mx_len;
    }
};
