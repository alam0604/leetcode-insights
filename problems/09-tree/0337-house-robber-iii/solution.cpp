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
    int rob(TreeNode* root) {
        pair<int, int> res = fun(root);
        return max(res.first, res.second);
    }
    pair<int, int> fun(TreeNode *root) {
        if(not root) return {0, 0};
        pair<int, int> a = fun(root->left);
        pair<int, int> b = fun(root->right);

        int include_root = root->val + a.second + b.second;
        int exclude_root = max(a.first, a.second) + max(b.first, b.second);
        return {include_root, exclude_root};
    }
};
