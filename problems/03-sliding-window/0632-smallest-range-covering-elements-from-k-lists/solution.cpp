// 632. Smallest Range Covering Elements from K Lists  [Hard]
// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/
// Accepted 2022-02-26 · Runtime 56 ms · Memory 16.6 MB

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<pair<int, int>> v;
        for(int i = 0; i < nums.size(); i++) {
            for(int j = 0; j < nums[i].size(); j++)
                v.push_back({nums[i][j], i + 1});
        }
        
        sort(v.begin(), v.end());
        int k = nums.size();
        int i = 0, j = 0;
        vector<int> visited(k + 1, 0);
        int l = 0, r = 0, mn = INT_MAX;
        while(j < v.size()) {
            int type = v[j].second;
            if(k > 0) {
                if(!visited[type]) k--;
                visited[type]++;
            }
            if(k == 0) {
                int diff = v[j].first - v[i].first;
                if(diff < mn) {
                    mn = diff;
                    l = v[i].first;
                    r = v[j].first;
                }
                int type2 = v[i].second;
                visited[type2]--;
                if(not visited[type2]) k++, j++;
                i++;
            }
            else j++;
        }
        return {l, r};
    }
};
