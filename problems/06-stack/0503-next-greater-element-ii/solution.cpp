// 503. Next Greater Element II  [Medium]
// https://leetcode.com/problems/next-greater-element-ii/
// Accepted 2022-05-04 · Runtime 49 ms · Memory 24.5 MB

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> st;
        int n = nums.size();
        for(int i = n - 2; i >= 0; i--)
            st.push(nums[i]);
        
        vector<int> res(n);
        for(int i = n - 1; i >= 0; i--) {
            while(not st.empty() and nums[i] >= st.top())
                st.pop();
            if(st.size() == 0)
                res[i] = -1;
            else res[i] = st.top();
            st.push(nums[i]);
        }
        return res;
    }
};
