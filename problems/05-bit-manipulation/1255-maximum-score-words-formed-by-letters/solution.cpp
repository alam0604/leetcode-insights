// 1255. Maximum Score Words Formed by Letters  [Hard]
// https://leetcode.com/problems/maximum-score-words-formed-by-letters/
// Accepted 2024-03-22 · Runtime 2 ms · Memory 11.6 MB

class Solution {
public:
    int mxScore = 0;
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        vector<int> l(26, 0);
        for(auto x : letters) l[x - 'a']++;
        fun(words, l, score, 0, 0);
        return mxScore;
    }
    
    void fun(vector<string>& w, vector<int> &l, vector<int> &score, int myScore, int idx) {
        
        if(idx == w.size()) {
            mxScore = max(mxScore, myScore);
            return;
        }
        fun(w, l, score, myScore, idx + 1);
        int points = 0, isPossible = 1;
        for(auto ch : w[idx]) {
            points += score[ch - 'a'];
            l[ch - 'a'] -= 1;
            if(l[ch - 'a'] < 0) isPossible = 0;
        }
        if(isPossible)
            fun(w, l, score, myScore + points, idx + 1);
        for(auto ch : w[idx])
            l[ch - 'a'] += 1;
    }
};
