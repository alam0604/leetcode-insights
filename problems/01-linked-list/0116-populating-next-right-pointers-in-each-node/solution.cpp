// 116. Populating Next Right Pointers in Each Node  [Medium]
// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
// Accepted 2022-01-13 · Runtime 41 ms · Memory 17.2 MB

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
        if(not root) return root;
        queue<Node*> q;
        q.push(root);
        
        while(not q.empty()) {
            int n = q.size();
            for(int i = 0; i < n; i++) {
                Node *p = q.front();
                q.pop();
                
                if(i == n - 1)
                    p -> next = nullptr;
                else {
                    p -> next = q.front();
                }
                
                if(p -> left) q.push(p -> left);
                if(p -> right) q.push(p -> right);
            }
        }
        return root;
    }
};
