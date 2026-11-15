// 212. Word Search II  [Hard]
// https://leetcode.com/problems/word-search-ii/
// Accepted 2022-11-05 · Runtime 849 ms · Memory 15.6 MB

class Solution {
public:
    struct node {
        node *links[26];
        int end;
        string str;
        node() {
            for(int i = 0; i < 26; i++) links[i] = nullptr;
            end = 0;
        }
    };
    node *root = new node();
    //-----------------------------------------------------------------------------

    void add(string &s) {
        node *t = root;
        for(auto x : s) {
            if(!t->links[x - 'a']) t->links[x - 'a'] = new node();
            t = t->links[x - 'a'];
        }
        t->end += 1;
        t->str = s;
    }

    vector<string> res;
    int vis[13][13];
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for(auto x : words)
            add(x);
        res.clear();
        memset(vis, 0, sizeof vis);
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[0].size(); j++) {
                if(root->links[board[i][j] - 'a'])
                    dfs(board, root, i, j);
            }
        }
        return res;
    }

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    void dfs(vector<vector<char>> &board, node *t, int i, int j) {
        int n = board.size(), m = board[0].size();
        if(i < 0 or j < 0 or i >= n or j >= m or !t or !t->links[board[i][j] - 'a'] or vis[i][j]) return;

        t = t->links[board[i][j] - 'a'];
        vis[i][j] = 1;
        if(t->end) {
            t->end--;
            res.push_back(t->str);
        }

        for(int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            dfs(board, t, x, y);
        }
        vis[i][j] = 0;
    }
};
