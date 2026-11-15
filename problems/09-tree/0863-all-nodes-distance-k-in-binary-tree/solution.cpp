// 863. All Nodes Distance K in Binary Tree  [Medium]
// https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
// Accepted 2022-01-05 · Runtime 4 ms · Memory 12.4 MB

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    
    bool getPath(TreeNode *root, vector<TreeNode *> &path, TreeNode* target) {
        if(not root) return false;
        
        if(root == target) {
            path.push_back(root);
            return true;
        }
        
        bool f1 = getPath(root -> left, path, target);
        bool f2 = getPath(root -> right, path, target);
        
        if(f1 or f2) {
            path.push_back(root);
            return true;
        }
        return false;
    }
    
    void getKDistanceNodes(TreeNode *root, vector<int> &ans, int k, TreeNode *blocker) {
        if(not root) return;
        if(root == blocker or k < 0) return;
        if(k == 0) {
            ans.push_back(root -> val);
            return;
        }
        
        getKDistanceNodes(root -> left, ans, k - 1, blocker);
        getKDistanceNodes(root -> right, ans, k - 1, blocker);
    }
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        
        if(not root) return {};
        vector<TreeNode *> path;
        
        getPath(root, path, target);
        
        vector<int> res;
        
        for(int i = 0; i < path.size(); i++) {
            if(k - i < 0)
                break;
            if(i == 0) {
                getKDistanceNodes(path[i], res, k - i, nullptr);
            }
            else
                getKDistanceNodes(path[i], res, k - i, path[i - 1]);
        }
        
        // sort(res.begin(), res.end());
        return res;
        
    }
};
