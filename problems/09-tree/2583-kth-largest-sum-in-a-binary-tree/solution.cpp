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
    unordered_map<int, long> mp;
    long long kthLargestLevelSum(TreeNode* root, int k) {
        vector<long> v; fun(root, 1);
        if(mp.size() < k) return -1;
        for(int i = 1; i <= mp.size(); i++) v.push_back(mp[i]);
        sort(v.rbegin(), v.rend());
        return v[k - 1];
    }

    void fun(TreeNode *r, int level) {
        if(not r) return;
        mp[level] += (long)r->val;
        fun(r->left, level + 1);
        fun(r->right, level + 1);
    }
};
