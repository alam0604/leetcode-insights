// 208. Implement Trie (Prefix Tree)  [Medium]
// https://leetcode.com/problems/implement-trie-prefix-tree/
// Accepted 2022-06-20 · Runtime 66 ms · Memory 44.9 MB

struct Node {
    Node *links[26];
    bool end = false;
};

class Trie {

private: Node *root;
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node *node = root;
        for(auto &ch : word) {
            if(not node->links[ch - 'a'])
                node->links[ch - 'a'] = new Node();
            node = node->links[ch - 'a'];
        }
        node->end = true;
    }
    
    bool search(string word) {
        Node *node = root;
        for(auto &ch : word) {
            if(not node->links[ch - 'a']) return false;
            node = node->links[ch - 'a'];
        }
        return node->end;
    }
    
    bool startsWith(string prefix) {
        Node *node = root;
        for(auto &ch : prefix) {
            if(not node->links[ch - 'a']) return false;
            node = node->links[ch - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
