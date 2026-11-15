// 82. Remove Duplicates from Sorted List II  [Medium]
// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// Accepted 2026-02-21 · Runtime 0 ms · Memory 15.5 MB

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
    ListNode* deleteDuplicates(ListNode* head) {
        if(not head or not head->next) return head;
        ListNode *prev = head, *curr = head, *root = nullptr, *last = nullptr;
        int flag = 0;
        while(curr) {
            while(curr and prev->val == curr->val) curr = curr->next;

            if(prev->next == curr) { 
                // prev is unique
                if(not flag) {
                    root = prev;
                    last = root;
                    flag = true;
                }
                else {
                    last->next = prev;
                    last = last->next;
                }
            }
            else {
                prev = curr;
            }
        }
        if(last) last->next = nullptr;
        return root;
    }
};
