// 19. Remove Nth Node From End of List  [Medium]
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/
// Accepted 2024-03-03 · Runtime 0 ms · Memory 13.2 MB

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head) return head;
        return fun(head, n);
    }

    ListNode* fun(ListNode *head, int &n) {
        if(!head) return nullptr;
        head->next = fun(head->next, n);
        n -= 1;
        if(n == 0) return head->next;
        return head;
    }



};
