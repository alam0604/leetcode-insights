class Solution {
public:
    vector<vector<string>> findMismatchedSegments(string s1, string s2) {
        vector<vector<string>> res;

        for(int i  = 0; i < s1.size(); i++) {
            if(s1[i] == s2[i]) continue;
            else {
                string out1 = "", out2 = "";
                vector<string> temp;
                while(i < s1.size() and s1[i] != s2[i]) {
                    out1.push_back(s1[i]);
                    out2.push_back(s2[i]);
                    i += 1;
                }
                temp.push_back(out1);
                temp.push_back(out2);
                res.push_back(temp);
            }
        }
        return res;
    }
};
