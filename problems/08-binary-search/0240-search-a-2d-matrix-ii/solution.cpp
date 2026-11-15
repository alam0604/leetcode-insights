// 240. Search a 2D Matrix II  [Medium]
// https://leetcode.com/problems/search-a-2d-matrix-ii/
// Accepted 2022-07-24 · Runtime 157 ms · Memory 15 MB

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
