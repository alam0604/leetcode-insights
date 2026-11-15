// 24. Swap Nodes in Pairs  [Medium]
// https://leetcode.com/problems/swap-nodes-in-pairs/
// Accepted 2026-04-17 · Runtime 0 ms · Memory 11.2 MB

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
    ListNode* swapPairs(ListNode* head) {
        if(!head or !head->next) return head;
        return fun(nullptr, head, head->next);
    }

    ListNode* fun(ListNode *p, ListNode *f, ListNode *s) {
        ListNode *t = s->next;
        f->next = t;
        s->next = f;
        if(p) p->next = s;

        if(t and t->next)
            fun(f, t, t->next);
        return s;
    }
};
