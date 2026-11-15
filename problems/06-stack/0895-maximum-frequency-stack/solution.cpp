// 895. Maximum Frequency Stack  [Hard]
// https://leetcode.com/problems/maximum-frequency-stack/
// Accepted 2022-03-19 · Runtime 375 ms · Memory 86.6 MB

class FreqStack {
public:
    unordered_map<int, stack<int>> mst;
    unordered_map<int, int> mp;
    int mx;
    FreqStack() {
        int mx = 0;
    }
    
    void push(int val) {
       mp[val]++;
        mx = max(mx, mp[val]);
        mst[mp[val]].push(val);
        // cout << mx << "\n";
    }
    
    int pop() {
        int x = mst[mx].top(); mst[mx].pop();
        if(mst[mx].size() == 0) mx--;
        mp[x]--;
        // cout << x << " : " << mx << endl;
        return x;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
