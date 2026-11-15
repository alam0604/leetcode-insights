// 1209. Remove All Adjacent Duplicates in String II  [Medium]
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
// Accepted 2022-05-06 · Runtime 34 ms · Memory 10 MB

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int>> st;
        st.push({'#', 0});
        for(auto x : s) {
            if(x != st.top().first)
                st.push({x, 1});
            else {
                pair<char, int> &p = st.top();
                p.second += 1;
                if(p.second == k)
                    st.pop();
            }
        }
        
        string t = "";
        while(st.size() > 1) {
            pair<char, int> p = st.top();
            st.pop();
            for(int i = 0; i < p.second; i++)
                t.push_back(p.first);
        }
        reverse(t.begin(), t.end());
        return t;
    }
};
