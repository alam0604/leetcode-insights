// 410. Split Array Largest Sum  [Hard]
// https://leetcode.com/problems/split-array-largest-sum/
// Accepted 2022-03-31 · Runtime 0 ms · Memory 7.2 MB

class Solution {
public:
    typedef long long ll;
    int splitArray(vector<int>& v, int m) {
        ll low = 0, high = 1e9;
        ll ans = 0;
       while (low < high) {
        ll mid = low + (high - low) / 2;

        ll c = 0, sum = 0;
        for (auto x : v) {
            if (x > mid) {
                c = 100;
                break;
            }
            sum += x;
            if (sum > mid) {
                c++;
                sum = x;
            }
        }
        c++;
        // cout << mid << sp << c << en;
        if (c <= m) {
            ans = mid;
            high = mid;
        }
        else
            low = mid + 1;
    }
        // cout << ans << en;
        return ans;
    }
};
