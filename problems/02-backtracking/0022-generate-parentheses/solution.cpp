// 22. Generate Parentheses  [Medium]
// https://leetcode.com/problems/generate-parentheses/
// Accepted 2022-01-06 · Runtime 7 ms · Memory 13.6 MB

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        solve(res, "", n, n);
        return res;
    }
    void solve(vector<string> &res, string output, int op, int cl) {
        if(not op and not cl) {
            res.push_back(output);
            return;
        }
        if(op == cl)
            solve(res, output + '(', op - 1, cl);
        else {
            if(op == 0)
                solve(res, output + ')', op, cl - 1);
            else {
                solve(res, output + '(', op - 1, cl);
                solve(res, output + ')', op, cl - 1);
            }
        }
    }
};
