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
    int countDominantNodes(TreeNode* root) {
        return fun(root).second;
    }

    pair<int, int> fun(TreeNode *root) {
        if(!root) return {0, 0};
        auto l = fun(root->left);
        auto r = fun(root->right);

        if(root->val >= max(l.first, r.first)) 
            return {root->val, l.second + r.second + 1};
        return {max(l.first, r.first), l.second + r.second};
    }
};
