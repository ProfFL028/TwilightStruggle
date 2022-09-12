// https://leetcode.cn/leetbook/read/top-interview-questions/x2959v/
#include  <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> n2;
        for (int i = 1; i <=100; i++) {
            n2.push_back(i*i);
        }
        vector<int> dp(n+1, 100001);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (auto k : n2) {
                if (i - k >= 0) {
                    dp[i] = min(dp[i], dp[i-k]+1);
                } else {
                    break;
                }
            }
        }
        return dp[n];
    }
};
int main() {
    Solution solution;

    return 0;
}