// 79. Word Search  [Medium]
// https://leetcode.com/problems/word-search/
// Accepted 2024-04-03 · Runtime 169 ms · Memory 9.5 MB

class Solution {
public:
int vis[11][11];
    bool exist(vector<vector<char>>& b, string w) {
        for(int i = 0; i < b.size(); i++)
          for(int j = 0; j < b[0].size(); j++)
              if(b[i][j] == w[0])
                if(fun(b, i, j, w, 1)) return 1;
         return 0;     
    }

    int fun(vector<vector<char>>& b, int i, int j, string &w, int idx) {
      if(idx >= w.size()) return 1;

      vis[i][j] = 1;
      int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
      for(int k = 0; k < 4; k++) {
        int new_i = i + dx[k], new_j = j + dy[k];
        if(new_i < 0 or new_j < 0 or new_i >= b.size() or new_j >= b[0].size() or vis[new_i][new_j])
          continue;
        if(b[new_i][new_j] == w[idx])
          if(fun(b, new_i, new_j, w, idx + 1)) return 1;
      }
      vis[i][j] = 0;
      return 0;
    }
};
