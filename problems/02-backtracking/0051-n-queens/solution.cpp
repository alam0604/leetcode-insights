// 51. N-Queens  [Hard]
// https://leetcode.com/problems/n-queens/
// Accepted 2026-01-16 · Runtime 0 ms · Memory 10 MB

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> out_list; string out = "";

        for(int i = 0; i < n; i++) out.push_back('.');
        for(int i = 0; i < n; i++) out_list.push_back(out);
        
        fun(n, 0, out_list, res);
        return res;
    }

    bool is_valid(vector<string> &out, int i, int j, int n) {

        int r = i, c = j;
        while(r >= 0) {
            if(out[r][c] == 'Q') return false;
            r--;
        }
        r = i, c = j;
        while(c >= 0) {
            if(out[r][c] == 'Q') return false;
            c--;
        }
        r = i, c = j;
        while(r >= 0 and c >= 0) {
            if(out[r][c] == 'Q') return false;
            r--, c--;
        }
        r = i, c = j;
        while(r >= 0 and c < n) {
            if(out[r][c] == 'Q') return false;
            r--, c++;
        }
        return true;
    }

    void fun(int &n, int i, vector<string> &out, vector<vector<string>> &res) {

        if(i >= n) {
            res.push_back(out);
            return;
        }
        for(int j = 0; j < n; j++) {
            if(is_valid(out, i, j, n)) {
                out[i][j] = 'Q';
                fun(n, i + 1, out, res);
                out[i][j] = '.';
            }
        }
        return;
    }

};
