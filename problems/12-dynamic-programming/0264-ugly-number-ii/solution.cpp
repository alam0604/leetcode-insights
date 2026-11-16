class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> pq;
        long ugly = 1; pq.push(ugly); unordered_map<long, long> mp; mp[ugly] = 1;
        for(int i = 0; i < n; i++) {
            ugly = pq.top(); pq.pop();
            for(auto p : {2, 3, 5}) {
                long ugly_val = ugly * (long)p;
                if(not mp[ugly_val]) {
                    mp[ugly_val] = 1;
                    pq.push(ugly_val);
                }
            }
        }
        return ugly;
    }
};
