// 767. Reorganize String  [Medium]
// https://leetcode.com/problems/reorganize-string/
// Accepted 2022-04-22 · Runtime 3 ms · Memory 6.2 MB

class Solution {
public:
    string reorganizeString(string s) {
        unordered_map<char, int> mp;
        for(auto x : s) mp[x]++;
        priority_queue<pair<int, char>> pq;
        
        for(auto x : mp)
            pq.push({x.second, x.first});
        string res = "";
        while(not pq.empty()) {
            pair<int, char> p = pq.top(); pq.pop();
            if(res.size() == 0) {
                res.push_back(p.second);
                p.first -= 1;
                if(p.first > 0)
                    pq.push(p);
            }
            else {
                if(p.second == res.back()) {
                    if(pq.size() > 0) {
                        pair<int, char> q = pq.top(); pq.pop();
                        res.push_back(q.second);
                        q.first -= 1;
                        if(q.first > 0)
                            pq.push(q);
                        pq.push(p);
                    }
                    else return "";
                }
                else {
                    res.push_back(p.second);
                    p.first -= 1;
                    if(p.first > 0)
                        pq.push(p);
                }
            }
        }
        return res;
    }
};
