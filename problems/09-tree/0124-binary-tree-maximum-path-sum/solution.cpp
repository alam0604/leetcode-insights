// 124. Binary Tree Maximum Path Sum  [Hard]
// https://leetcode.com/problems/binary-tree-maximum-path-sum/
// Accepted 2022-12-11 · Runtime 65 ms · Memory 28.8 MB

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
private:
    int mx_sum;
public:
    int maxPathSum(TreeNode* root) {
       mx_sum = INT_MIN;
       fun(root);
       return mx_sum; 
    }

    int fun(TreeNode *root) {
        if(!root) return 0;
        int l = fun(root->left);
        int r = fun(root->right);

        if(mx_sum == INT_MIN) mx_sum = root->val;
        else
            mx_sum = max({mx_sum, root->val, root->val + l, root->val + r, root->val + l + r});
        return max({l + root->val, r + root->val, root->val});
    }
};
