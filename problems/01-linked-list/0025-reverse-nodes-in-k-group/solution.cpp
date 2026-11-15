// 25. Reverse Nodes in k-Group  [Hard]
// https://leetcode.com/problems/reverse-nodes-in-k-group/
// Accepted 2022-06-09 · Runtime 15 ms · Memory 11.4 MB

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
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        ListNode *t = head;
        int len = 0;
        while(t) {len++; t = t->next;}
        
        ListNode *p = nullptr, *l = nullptr, *m = nullptr, *h = head;
        ListNode *temp = h;
        int i = 0;
        len -= len % k;
        while(i < len) {
            
            
            l = m;
            m = h;
            h = h->next;
            m->next = l;
            
            if(i % k == k - 1) {
                if(not p) {
                    p = temp;
                    head = m;
                }
                else {
                    p->next = m;
                    p = temp;
                }
                temp = h;
                m = nullptr;
            }
            i++;
        }
        // cout << p->val << " : " << h->val << "\n";
        if(h) p->next = h;
        return head;
    }
};
