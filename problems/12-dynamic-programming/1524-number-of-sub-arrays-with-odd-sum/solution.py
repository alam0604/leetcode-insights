class Solution:
    def numOfSubarrays(self, arr: list[int]) -> int:
        sum, res, odd, eve = 0, 0, 0, 0
        md = 1e9 + 7
        for val in arr:
            sum += val
            if sum & 1:
                res += 1
                odd += 1
                res = int((res + eve) % md)
            else:
                eve += 1
                res = int((res + odd) % md)
        return res

        
