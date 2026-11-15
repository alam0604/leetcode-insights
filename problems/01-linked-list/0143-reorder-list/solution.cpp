// 143. Reorder List  [Medium]
// https://leetcode.com/problems/reorder-list/
// Accepted 2022-02-10 · Runtime 44 ms · Memory 18.4 MB

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

/*
Algorithm :
step 1 : find the mid of the linkedList using slow and fast pointers
step 2 : reverse the linked list from middle to end
step 3 : run a recursive function to add the firat half list with the reversed other half of it
*/

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while(fast and fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        ListNode *mid = slow->next;
        slow->next = nullptr;
        mid = reverse(mid, nullptr);
        head = fun(head, mid);
    }
    
    ListNode *fun(ListNode *h1, ListNode *h2) {
        if(not h2) return nullptr;
        ListNode *t1 = h1->next, *t2 = h2;
        h2 = h2->next;
        
        h1->next = t2;
        t2->next = t1;
        fun(t1, h2);
        return h1;
    }
    
    ListNode *reverse(ListNode *p, ListNode *q) {
        if(p == nullptr) return q;
        
        ListNode *head = reverse(p->next, p);
        p->next = q;
        return head;
    }
};
