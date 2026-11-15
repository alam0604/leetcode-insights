// 4. Median of Two Sorted Arrays  [Hard]
// https://leetcode.com/problems/median-of-two-sorted-arrays/
// Accepted 2022-10-02 · Runtime 53 ms · Memory 89.4 MB

class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        if(m < n)
            return findMedianSortedArrays(B, A);
        
        int l = 0, r = n;
        while (l <= r) {
            int m1 = (l + r) >> 1;
            int m2 = ((n + m + 1) >> 1) - m1;

            int l1 = m1 == 0 ? INT_MIN : A[m1 - 1];
            int l2 = m2 == 0 ? INT_MIN : B[m2 - 1];
            int r1 = m1 == n ? INT_MAX : A[m1];
            int r2 = m2 == m ? INT_MAX : B[m2];

            if(l1 <= r2 && l2 <= r1){
                if((n + m) & 1)
                    return  max(l1, l2);
                return (max(l1, l2) * 1.0 + min(r1, r2) * 1.0) / 2.0;
            }
            if(l1 < r2)
                l = m1 + 1;
            else r = m1 - 1;
        }
        return 0;
    }
};
