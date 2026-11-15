// 148. Sort List  [Medium]
// https://leetcode.com/problems/sort-list/
// Accepted 2025-10-09 · Runtime 12 ms · Memory 24.8 MB

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* get_mid(struct ListNode *head) {
    if(!head || !head->next) return head;
    struct ListNode *slow = head, *fast = head;
    while(fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct ListNode* merge(struct ListNode *left, struct ListNode *right) {

    if(!left && !right) return NULL;
    if(!left) return right;
    if(!right) return left;    

    struct ListNode dummy; dummy.next = NULL;
    struct ListNode *last; last = &dummy;
    struct ListNode *root = last;

    while(left && right) {
        if(left->val <= right->val) {
            last->next = left;
            last = left;
            left = left->next;
        }
        else {
            last->next = right;
            last = right;
            right = right->next;
        }
    }
    if(!right) last->next = left;
    if(!left) last->next = right;

    return root->next;
}
struct ListNode * divide(struct ListNode *head) {
    if(!head || !head->next) return head;
    struct ListNode *mid = get_mid(head);
    struct ListNode *left, *right;
    right = mid->next;
    left = head; mid->next = NULL;

    struct ListNode *l = divide(left);
    struct ListNode *r = divide(right);
    // assuming both left & right lists are sorted now
    return merge(l, r);
}

struct ListNode* sortList(struct ListNode* head) {
    if(!head || !head->next) return head;
    return divide(head);
}
