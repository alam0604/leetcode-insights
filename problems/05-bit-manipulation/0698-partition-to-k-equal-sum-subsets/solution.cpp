// 698. Partition to K Equal Sum Subsets  [Medium]
// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
// Accepted 2022-07-16 · Runtime 1067 ms · Memory 9.5 MB

class Solution {
public:
    int vis[20];
     bool solve(vector<int>& nums,int target, int currsum, int i, int k) {
        if (k == 1) 
            return true;
        if(i>=nums.size()) return false;
        if (currsum == target) 
            return solve(nums, target, 0, 0, k-1);
        
        for (int j = i; j < nums.size(); j++) {
            if (vis[j]==1 || currsum + nums[j] > target) continue;
            
            vis[j] = 1;
            if (solve(nums,  target, currsum + nums[j], j+1, k)) return true;
            vis[j]=0;
        }
        
        return false;
    }
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        sum = accumulate(nums.begin(), nums.end(), sum);
        if (nums.size() < k || sum % k) return false;
        sort(nums.begin(),nums.end(),greater<int>());
        return solve(nums, sum / k, 0, 0, k);
    }
    
   
};
