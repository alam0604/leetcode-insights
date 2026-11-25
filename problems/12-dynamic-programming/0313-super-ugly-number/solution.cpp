class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& p) {
        int v[p.size()]; memset(v, 0, sizeof v);
        
        int res[n]; res[0] = 1;
        for(int i = 1; i < n; i++) {
            priority_queue<long, vector<long>, greater<long>> pq;
            for(int j = 0; j < p.size(); j++)
                pq.push((long)res[v[j]] * (long)p[j]);
            res[i] = pq.top();
            for(int j = 0; j < p.size(); j++)
                if(res[i] == ((long)res[v[j]] * (long)p[j])) v[j] += 1;
        }
        return res[n - 1];
    }
};
