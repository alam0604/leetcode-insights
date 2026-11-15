// 1008. Construct Binary Search Tree from Preorder Traversal  [Medium]
// https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
// Accepted 2022-01-21 · Runtime 11 ms · Memory 13.8 MB

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
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return fun(preorder, i, INT_MAX);
    }
    
    TreeNode* fun(vector<int>& preorder, int &i, int bound) {
        // static int i = 0;
        if(i >= preorder.size() or preorder[i] > bound) return nullptr;
        TreeNode *node = new TreeNode(preorder[i++]);
        // i++;
        node->left = fun(preorder, i, node->val);
        // i++;
        node->right = fun(preorder, i, bound);
        return node;
    }
    
};
