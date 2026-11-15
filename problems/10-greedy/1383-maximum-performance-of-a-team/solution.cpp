// 1383. Maximum Performance of a Team  [Hard]
// https://leetcode.com/problems/maximum-performance-of-a-team/
// Accepted 2022-09-11 · Runtime 378 ms · Memory 48 MB

#include <bits/stdc++.h>
using namespace std;
#define vc vector
#define ll long long
#define all(v) v.begin(), v.end()
#define len(v) return v.size()
const ll mod = 1e9 + 7;

class Solution {
public:
    int maxPerformance(int n, vector<int>& s, vector<int>& e, int k) {
        vc<vc<ll>> v;
        for(int i = 0; i < n; i++)
            v.push_back({(ll)s[i], (ll)e[i]});
        
        sort(v.begin(), v.end(), [&] (vc<ll> &a, vc<ll> &b) {
            return a[1] > b[1];
        });
        // for(auto x : v) cout << x.first << ":" << x.second << '\n';
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        ll res = 0, speed = 0;
        for(int i = 0; i < k; i++) {
            speed += v[i][0];
            pq.push(v[i][0]);
            res = max(res, speed * v[i][1]);
        }
        for(int i = k; i < n; i++) {
            if(v[i][0] > pq.top()) {
                speed -= pq.top(); pq.pop();
                speed += v[i][0]; pq.push(v[i][0]);
                res = max(res, speed * v[i][1]);
            }
        }
        return res % mod;
    }
};
