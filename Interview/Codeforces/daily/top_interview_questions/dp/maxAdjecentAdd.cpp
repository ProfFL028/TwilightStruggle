// https://leetcode.cn/leetbook/read/top-interview-questions/x25oeg/
#include  <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2,0));
        dp[0][1]= nums[0];
        for (int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
            dp[i][1] = dp[i-1][0]+nums[i];
        }

        return max(dp[n-1][0], dp[n-1][1]);
    }
};

int main() {
    Solution solution;

    return 0;
}