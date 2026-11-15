// 328. Odd Even Linked List  [Medium]
// https://leetcode.com/problems/odd-even-linked-list/
// Accepted 2022-01-02 · Runtime 31 ms · Memory 10.6 MB

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
    ListNode* oddEvenList(ListNode* head) {
        
        if(not head) return head;
        
        ListNode *h1 = head, *h2 = nullptr, *t = nullptr;
        int cnt = 1;
        if(head -> next) h2 = head -> next;
        else return head;
        
        while(h2) {
            if((cnt & 1) == 0) {
                
                t -> next = h2 -> next;
                h2 -> next = h1 -> next;
                h1 -> next = h2;
                
                h1 = h1 -> next;
                h2 = t -> next;
                cnt++;
            }
            else {
                t = h2;
                h2 = h2 -> next;
                cnt++;
            }
        }
        
        return head;
        
    }
};
