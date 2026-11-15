// 236. Lowest Common Ancestor of a Binary Tree  [Medium]
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
// Accepted 2022-07-26 · Runtime 30 ms · Memory 14.3 MB

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return getLCA(root, p, q);
    }
    
    TreeNode* getLCA(TreeNode *root, TreeNode* p, TreeNode* q) {
        if(not root) return nullptr;
        
        if(root == p or root == q) return root;
        
        TreeNode *left = getLCA(root -> left, p, q);
        TreeNode *right = getLCA(root -> right, p, q);
        
        if(left and right) return root;
        if(left) return left;
        if(right) return right;
        return nullptr;
    }
};
