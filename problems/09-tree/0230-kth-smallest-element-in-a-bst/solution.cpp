// 230. Kth Smallest Element in a BST  [Medium]
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
// Accepted 2022-04-18 · Runtime 22 ms · Memory 24.1 MB

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
    int kthSmallest(TreeNode* root, int k) {
        int res = -1;
        getKthSmallest(root, k, res);
        return res;
    }
    void getKthSmallest(TreeNode *root, int &k, int &res) {
        if(not root) return;
        getKthSmallest(root->left, k, res);
        k -= 1;
        if(k == 0) res = root->val;
        getKthSmallest(root->right, k, res);
    }
};
