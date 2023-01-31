// https://leetcode.cn/problems/count-number-of-ways-to-place-houses/
// dp
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    /**
     * dp[n] = dp[n-1]+dp[n-2]
     * @param n
     * @return
     */
    int countHousePlacements(int n) {
        if (n <=2) {
            return n * n ;
        }
        const int MOD = 1e9+7;
        vector<long long> dp(n+1, 0);
        dp[1] = 2;
        dp[2] = 3;
        for (int i = 3; i <=n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
            dp[i] = dp[i] % MOD;
        }

        return dp[n]* dp[n] % MOD;
    }
};

int main() {
    Solution solution;

    return 0;
}
