// 1249. Minimum Remove to Make Valid Parentheses  [Medium]
// https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
// Accepted 2022-03-15 · Runtime 43 ms · Memory 13.1 MB

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<pair<char, int>> st;
        
        for(int i = 0; i < s.size(); i++) {
            char ch = s[i];
            if(ch == '(')
                st.push({ch, i});
            else if(ch == ')') {
                if(st.size() > 0 and st.top().first == '(') st.pop();
                else st.push({ch, i});
            }
            else continue;
        }
        string out = "";
        for(int i = s.size() - 1; i >= 0; i--) {
            if(st.size() > 0) {
                int idx = st.top().second;
                if(idx == i) {
                    st.pop();
                    continue;
                }
                out += s[i];   
            }
            else out += s[i];
        }
        reverse(out.begin(), out.end());
        return out;
    }
};
