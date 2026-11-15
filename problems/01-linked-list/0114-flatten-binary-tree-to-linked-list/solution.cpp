// 114. Flatten Binary Tree to Linked List  [Medium]
// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
// Accepted 2022-07-27 · Runtime 7 ms · Memory 12.7 MB

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
    TreeNode *pre;
    void fun(TreeNode *root) {
        if(not root) return;
        fun(root->right);
        fun(root->left);
        
        root->right = pre;
        root->left = nullptr;
        pre = root;
    }
    void flatten(TreeNode* root) {
        if(not root) return;
        pre = nullptr;
        TreeNode *head = nullptr;
        fun(root);
    }
};
