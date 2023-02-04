// https://leetcode.cn/problems/maximum-number-of-consecutive-values-you-can-make/
// brain tease
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int getMaximumConsecutive(vector<int> coins) {
        int ans = 0;
        sort(coins.begin(), coins.end());
        for (auto &coin: coins) {
            if (ans >= coin) {
                ans += coin;
            }
        }

        return ans;
    }
};

int main() {
    Solution solution;

    return 0;
}
