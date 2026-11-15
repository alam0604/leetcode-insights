// 32. Longest Valid Parentheses  [Hard]
// https://leetcode.com/problems/longest-valid-parentheses/
// Accepted 2022-05-24 · Runtime 7 ms · Memory 7.2 MB

class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.size() == 0) return 0;
        stack<int> idx;
        idx.push(-1);
        int ans = 0;
        for(int i = 0; i < s.size(); i++) {
            char x = s[i];
            if(x == '(') idx.push(i);
            else {
                int pos = idx.top();
                if(pos == -1 or s[pos] == ')')
                    idx.push(i);
                else {
                    idx.pop();
                    int val = i - idx.top();
                    ans = max(val, ans);
                }
            }
        }
        return ans;
    }
};
