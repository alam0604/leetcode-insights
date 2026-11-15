// 968. Binary Tree Cameras  [Hard]
// https://leetcode.com/problems/binary-tree-cameras/
// Accepted 2022-06-17 · Runtime 16 ms · Memory 21.3 MB

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
    int cameras;
    int minCameraCover(TreeNode* root) {
        
        cameras = 0;
        fun(root, root);
        return cameras;
    }
    
    int fun(TreeNode *root, TreeNode *head) {
        if(not root) return 0;
        
        int l = fun(root->left, head);
        int r = fun(root->right, head);
        
        if(l == 0 and r == 0 and root == head) {
            cameras++;
            return 0;
        }
        if(l == 1 or r == 1) {
            cameras++;
            return 2;
        }
        else if(l == 2 or r == 2) return 0;
        
        else if(l == 0 and r == 0) return 1;
        return 0;
    }
};
