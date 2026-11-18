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
    int pathSum(TreeNode* r, int t) {
        if(not r) return 0;
        int a, b, c; a = b = c = 0;
        a = pathSum(r->left, t);
        b = pathSum(r->right, t);
        c = fun(r, (long)t);
        return a + b + c;
    }

    int fun(TreeNode *r, long t) {
        if(not r) return 0;
        int cnt = 0;
        if(r->val == t) 
            cnt = 1; // we could have just returned 1 but what if next node have values as 0. Every consecutive 0 will increase the count by 1 hence we let the functions to call again below

        cnt += fun(r->left, (long)t - (long)r->val);
        cnt += fun(r->right, (long)t - (long)r->val);
        return cnt;
    }
};
