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
    unordered_map<int, int> mp; int mx = 0;
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> res; fun(root);
        for(auto x : mp)
            if (x.second == mx) res.push_back(x.first);
        return res;
    }
    int fun(TreeNode *root) {
        if(not root) return 0;
        int sum = fun(root->left) + fun(root->right) + root->val;
        mp[sum]++; mx = max(mx, mp[sum]);
        return sum;
    }
};
