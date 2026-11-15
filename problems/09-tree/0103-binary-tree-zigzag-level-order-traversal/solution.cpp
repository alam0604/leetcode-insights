// 103. Binary Tree Zigzag Level Order Traversal  [Medium]
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
// Accepted 2023-04-20 · Runtime 0 ms · Memory 12 MB

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        int f = 0; queue<TreeNode *> q;
        q.push(root);
        while(!q.empty()) {
            int n = q.size();
            vector<int> dummy;
            for(int i = 0; i < n; i++) {
                TreeNode *p = q.front(); q.pop();
                dummy.push_back(p->val);
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            if(f) reverse(dummy.begin(), dummy.end());
            f ^= 1;
            res.push_back(dummy);
        }
        return res;
    }
};
