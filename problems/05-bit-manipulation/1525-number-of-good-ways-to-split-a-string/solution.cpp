// 1525. Number of Good Ways to Split a String  [Medium]
// https://leetcode.com/problems/number-of-good-ways-to-split-a-string/
// Accepted 2022-08-25 · Runtime 42 ms · Memory 9.2 MB

class Solution {
public:
    int numSplits(string s) {
        
        int n = s.size();
        int l[n]; memset(l, 0, sizeof l);
        int r[n]; memset(r, 0, sizeof r);
        
        unordered_set<char> st;
        for(int i = 0; i < n; i++) {
            if(st.find(s[i]) == st.end())
                l[i] = (i == 0 ? 1 : l[i - 1] + 1);
            else l[i] = l[i - 1];
            st.insert(s[i]);
        }
        st.clear();
        for(int i =  n - 1; i >= 0; i--) {
            if(st.find(s[i]) == st.end())
                r[i] = (i == n - 1 ? 1 : r[i + 1] + 1);
            else r[i] = r[i + 1];
            st.insert(s[i]);
        }
        
        int cnt = 0;
        for(int i = 0; i < n - 1; i++)
            cnt += l[i] == r[i + 1];
        return cnt;
    }
};
