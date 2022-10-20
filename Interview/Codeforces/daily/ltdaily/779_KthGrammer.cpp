// leetcode: https://leetcode.cn/problems/k-th-symbol-in-grammar/submissions/

#include <bit/stdc++.h>

using namespace std;
class Solution {
public:
    int kthGrammar(int n, int k) {
        // return __builtin_popcount(k - 1) & 1;
        k--;
        int res = 0;
        while (k > 0) {
            k &= k - 1;
            res ^= 1;
        }
        return res;
    }
};

int main() {
    Solution solution;


    return 0;
}