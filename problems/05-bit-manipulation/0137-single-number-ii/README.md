# 137. Single Number II

**Difficulty:** 🟡 Medium  
**Topics:** Array, Bit Manipulation  
**Problem:** [https://leetcode.com/problems/single-number-ii/](https://leetcode.com/problems/single-number-ii/)

## My accepted submissions

| # | Language | Accepted on | Runtime | Memory | Code |
|---|---|---|---|---|---|
| 1 | C++ | 2026-11-16 | 2 ms (beats 47.3%) | 16.1 MB (beats 27.7%) | [`solution-1.cpp`](./solution-1.cpp) |
| 2 | C++ | 2026-11-16 | 1 ms (beats 55.9%) | 16.1 MB (beats 27.7%) | [`solution-2.cpp`](./solution-2.cpp) |

**Solution 1** counts the set bits at every position into a 32-slot array first, then rebuilds the answer from the positions whose count isn't a multiple of 3.

**Solution 2** does the same bit counting, but handles one bit position at a time with a single counter, so it needs no extra array.
