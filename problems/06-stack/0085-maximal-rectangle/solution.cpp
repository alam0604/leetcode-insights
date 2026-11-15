// 85. Maximal Rectangle  [Hard]
// https://leetcode.com/problems/maximal-rectangle/
// Accepted 2022-08-04 · Runtime 105 ms · Memory 14.7 MB

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& mat) {
        
        int n = mat.size(), m = mat[0].size();
        vector<int> v(m, 0);
        
        int mx_area = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(mat[i][j] == '1')
                    v[j]++;
                else v[j] = 0;
            }
            
            mx_area = max(mx_area, get_area(v));
        }
        return mx_area;
    }
    
    int get_area(vector<int> &v) {
        
        vector<int> l(v.size(), 0), r(v.size(), 0);
        stack<pair<int, int>> st;
        int n = v.size();
        for(int i = 0; i < v.size(); i++) {
            while(not st.empty() and v[i] <= st.top().first)
                st.pop();
            if(st.empty()) l[i] = -1;
            else l[i] = st.top().second;
            st.push({v[i], i});
        }
        
        while(not st.empty()) st.pop();
        
        for(int i = v.size() - 1; i >= 0; i--) {
            while(not st.empty() and v[i] <= st.top().first)
                st.pop();
            if(st.empty()) r[i] = n;
            else r[i] = st.top().second;
            st.push({v[i], i});
        }
        
        int area = 0;
        for(int i = 0; i < v.size(); i++)
            area = max(area, (r[i] - l[i] - 1) * v[i]);
        return area;
    }
};
