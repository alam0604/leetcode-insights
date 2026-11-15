// 106. Construct Binary Tree from Inorder and Postorder Traversal  [Medium]
// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// Accepted 2022-01-11 · Runtime 91 ms · Memory 25.7 MB

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
    
    TreeNode* createTree(vector<int> &in, int in_s, int in_e, vector<int> &post, int ps_s,                              int ps_e) {
        
        
        if(in_s > in_e or ps_s > ps_e) return nullptr;
        int index = in_s;
        while(in[index] != post[ps_e]) index++;
        int count = index - in_s;
        
        TreeNode *root = new TreeNode(post[ps_e]);
        root -> left = createTree(in, in_s, index - 1, post, ps_s, ps_s + count - 1);
        root -> right = createTree(in, index + 1, in_e, post, ps_s + count, ps_e - 1);
        
        return root;
    }
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        TreeNode *root = createTree(inorder, 0, n - 1, postorder, 0, n - 1);
        return root;
    }
};
