// https://leetcode.cn/leetbook/read/top-interview-questions/x2echt/
#include  <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0)
            return 0;
        sort(coins.begin(), coins.end());
        vector<int> dp(amount+1, 100001);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (auto k : coins) {
                if (i - k >= 0) {
                    dp[i] = min(dp[i], dp[i-k]+1);
                } else {
                    break;
                }
            }
        }
        return dp[amount] == 100001 ? -1 : dp[amount];
    }
};
int main() {
    Solution solution;

    return 0;
}