// 23. Merge k Sorted Lists  [Hard]
// https://leetcode.com/problems/merge-k-sorted-lists/
// Accepted 2022-06-07 · Runtime 1208 ms · Memory 13.6 MB

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        ListNode *root = new ListNode (-1);
        ListNode *prev = root;
        
        int n = lists.size();
        
        while(true) {
            
            ListNode *temp = new ListNode(INT_MAX);
            
            int idx = -1;
            for(int i = 0; i < n; i++) {
                if(lists[i] == nullptr) continue;
                
                if(lists[i]->val < temp->val) {
                    idx = i;
                    temp = lists[i];
                }
            }
            
            if(idx == -1) break;
            
            ListNode *t = lists[idx];
            lists[idx] = lists[idx]->next;
            prev->next = t;
            prev = t;
        }
        return root->next;
    }
};
