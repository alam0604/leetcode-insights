// 105. Construct Binary Tree from Preorder and Inorder Traversal  [Medium]
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// Accepted 2022-07-14 · Runtime 48 ms · Memory 25.9 MB

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
#define vc vector
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        return fun(preorder, 0, n - 1, inorder, 0, n - 1);
    }
    
    TreeNode *fun(vc<int> &pre, int ps, int pe, vc<int> &in, int is, int ie) {
        if(is > ie or ps > pe) return nullptr;
        
        int idx = is, count = 0;
        while(in[idx] != pre[ps]) idx++;
        count = idx - is;
        
        TreeNode *root = new TreeNode(pre[ps]);
        root->left = fun(pre, ps + 1, ps + count, in, is, idx - 1);
        root->right = fun(pre, ps + count + 1, pe, in, idx + 1, ie);
        
        return root;
    }
};
