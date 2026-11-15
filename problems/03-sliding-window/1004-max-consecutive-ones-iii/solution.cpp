// 1004. Max Consecutive Ones III  [Medium]
// https://leetcode.com/problems/max-consecutive-ones-iii/
// Accepted 2022-01-02 · Runtime 56 ms · Memory 55.4 MB

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        
        int n = nums.size();
        int i = 0, j = 0, tk = k, cnt = 0;
        int ans =  0;
        
        while(j < n) {
            if(nums[j] == 1) {
                cnt++;
                j++;
            }
            else {
                if(k > 0) {
                    cnt++;
                    j++;
                    k--;
                }
                
                else {
                    ans = max(ans, cnt);
                    if(nums[i] == 0) {
                        k++;
                        i++, cnt--;
                    }
                    else {
                        cnt--;
                        i++;
                    }
                }
            }
        }
        ans = max(ans, cnt);
        return ans;
    }
};
