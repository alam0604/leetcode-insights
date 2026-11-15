// 235. Lowest Common Ancestor of a Binary Search Tree  [Medium]
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// Accepted 2022-08-12 · Runtime 38 ms · Memory 23.3 MB

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
        if(not root) return nullptr;
        if(p->val < root->val and q->val < root->val)
            return lowestCommonAncestor(root->left, p, q);
        else if(p->val > root->val and q->val > root->val)
            return lowestCommonAncestor(root->right, p, q);
        return root;
    }
};
