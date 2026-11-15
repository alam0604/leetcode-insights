// 784. Letter Case Permutation  [Medium]
// https://leetcode.com/problems/letter-case-permutation/
// Accepted 2022-01-16 · Runtime 18 ms · Memory 11.5 MB

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> res;
        fun(res, s, "");
        return res;
    }
    
    void fun(vector<string> &res, string s, string out) {
        if(s.size() == 0) {
            res.push_back(out);
            return;
        }
        
        char ch = s[0];
        s.erase(s.begin(), s.begin() + 1);
        if(isalpha(ch)) {
            string out1 = out, out2 = out;
            out1 += tolower(ch), out2 += toupper(ch);
            fun(res, s, out1);
            fun(res, s, out2);
        }
        else {
            out += ch;
            fun(res, s, out);
        }
    }
};
