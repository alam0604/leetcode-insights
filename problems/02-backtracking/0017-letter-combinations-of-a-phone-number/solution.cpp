// 17. Letter Combinations of a Phone Number  [Medium]
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// Accepted 2022-05-09 · Runtime 5 ms · Memory 6.6 MB

class Solution {
public:
    vector<string> phone = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> letterCombinations(string digits) {
        
        vector<string> out;
        if(digits.size() == 0) return out;
        string curr = "";
        
        fun(digits, out, curr, 0);
        return out;
    }
    
    void fun(string digi, vector<string> &out, string &curr, int s) {
        if(s >= digi.size()) {
            out.push_back(curr);
            return;
        }
        
        for(auto x : phone[(digi[s] - '0')]) {
            curr.push_back(x);
            fun(digi, out, curr, s + 1);
            curr.erase(curr.begin() + curr.size() - 1, curr.end());
        }
    }
};
