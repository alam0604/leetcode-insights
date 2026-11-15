// 74. Search a 2D Matrix  [Medium]
// https://leetcode.com/problems/search-a-2d-matrix/
// Accepted 2022-03-30 · Runtime 4 ms · Memory 9.5 MB

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        int i = 0, j = m - 1;
        while(i < n and i >= 0 and j >= 0 and j < m) {
            if(target == matrix[i][j]) return true;
            else if(target < matrix[i][j]) j--;
            else i++;
        }
        return false;
    }
};
