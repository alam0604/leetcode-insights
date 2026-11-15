// 630. Course Schedule III  [Hard]
// https://leetcode.com/problems/course-schedule-iii/
// Accepted 2022-06-23 · Runtime 271 ms · Memory 56.2 MB

#define vc vector
class Solution {
public:
    static inline bool comp(vc<int> &a, vc<int> &b) {
        return a[1] < b[1];
    }
    int scheduleCourse(vector<vector<int>>& c) {
        int pre = 0;
        priority_queue<int> pq;
        
        sort(c.begin(), c.end(), comp);
        
        for(auto &x : c) {
            if(pre + x[0] <= x[1]) {
                pq.push(x[0]);
                pre += x[0];
            }
            else {
                if(not pq.empty() and pq.top() >= x[0]) {
                    pre -= pq.top();
                    pq.pop();
                    pre += x[0];
                    pq.push(x[0]);
                }
            }
        }
        return pq.size();
    }
};
