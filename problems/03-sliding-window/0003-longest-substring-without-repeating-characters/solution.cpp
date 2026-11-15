// 3. Longest Substring Without Repeating Characters  [Medium]
// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// Accepted 2026-02-11 · Runtime 0 ms · Memory 11.7 MB

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> vis(280, 0);
        int i = 0, j = 0, mx_len = 0;
        while(j < s.size()) {
            vis[s[j]] += 1;
            while(vis[s[j]] > 1) {
                vis[s[i]] -= 1;
                i += 1;
            }
            mx_len = max(mx_len, j - i + 1);
            j += 1;
        }
        return mx_len;
    }
};
