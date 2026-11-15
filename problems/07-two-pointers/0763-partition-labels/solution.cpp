// 763. Partition Labels  [Medium]
// https://leetcode.com/problems/partition-labels/
// Accepted 2022-03-21 · Runtime 8 ms · Memory 6.8 MB

class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> vc;
        unordered_map<char,int> mp;
        for(int i = 0; i < s.length(); i++)
            mp[s[i]] = i;
        int p = -1, i = 0;
        while(i < s.size())
        {
            int end = mp[s[i]];
            for(int j = i; j <= end; j++) {
                if(mp[s[j]] > end)
                    end = mp[s[j]];
            }
            // cout<<"end: "<<ss<<" "<<ss.length()<<"\n";
            cout << i << " : " << end << endl;
            vc.push_back(end - p);
            p = end;
            i = end + 1;
        }
        return vc;
    }
};
