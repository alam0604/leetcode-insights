class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(i == 0 or i == n - 1 or j == 0 or j == m - 1) {
                    if(board[i][j] == 'O' and not visited[i][j])
                        dfs(board, visited, i, j, 'O');
                }
            }
        }
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++)
                if(board[i][j] == 'O' and not visited[i][j])
                    dfs(board, visited, i, j, 'X');
        }
    }
    
    void dfs(vector<vector<char>>& board, vector<vector<bool>> &visited, int x, int y, char filler) {
        board[x][y] = filler;
        visited[x][y] = true;
        
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        int n = board.size(), m = board[0].size();
        
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if(nx < 0 or ny < 0 or nx >= n or ny >= m) continue;
            if(board[nx][ny] != 'O' or visited[nx][ny]) continue;
            
            dfs(board, visited, nx, ny, filler);
        }
    }
};
