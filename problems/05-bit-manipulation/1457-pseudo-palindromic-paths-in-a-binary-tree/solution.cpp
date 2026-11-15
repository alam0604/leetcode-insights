// 1457. Pseudo-Palindromic Paths in a Binary Tree  [Medium]
// https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/
// Accepted 2022-09-14 · Runtime 895 ms · Memory 188.6 MB

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int res, odd;
    void fun(TreeNode *root, map<int, int> &mp) {
        if(!root) return;
        if(!root->left and !root->right) {
            int a = root->val;
            mp[a]++;
            if(mp[a] & 1) odd++;
            else odd--;
            
            if(odd <= 1) res++;
            
            mp[a]--;
            if(mp[a] & 1) odd++;
            else odd--;
        }
        
        int a = root->val;
        mp[a]++;
        if(mp[a] & 1) odd++;
        else odd--;
        
        fun(root->left, mp);
        fun(root->right, mp);
        
        mp[a]--;
        if(mp[a] & 1) odd++;
        else odd--;
    }
    int pseudoPalindromicPaths (TreeNode* root) {
        odd = 0, res = 0;
        map<int, int> mp;
        fun(root, mp);
        return res;
    }
};
