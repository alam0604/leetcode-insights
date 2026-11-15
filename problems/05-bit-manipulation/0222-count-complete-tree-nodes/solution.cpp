// 222. Count Complete Tree Nodes  [Medium]
// https://leetcode.com/problems/count-complete-tree-nodes/
// Accepted 2022-11-15 · Runtime 76 ms · Memory 30.7 MB

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
    int countNodes(TreeNode* root) {
        if(not root) return 0;
        
        int left = countNodes(root->left);
        int right = countNodes(root->right);
        
        return (left + right + 1);
    }
};
