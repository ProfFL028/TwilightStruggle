// https://leetcode.cn/leetbook/read/top-interview-questions/xmguej/

#include <iostream>

using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int old = 0;
        int n = gas.size();
        int ans = 0;
        int cur = gas[0];
        for (int i = 1; i < n; i++) {
            if (cur - cost[i-1] < 0) {
                old += cur-cost[i-1];
                cur = gas[i];
                ans = i;
            } else {
                cur = cur - cost[i-1] + gas[i];
            }
        }
        if (cur + old - cost[n-1] >=0) {
            return ans;
        }

        return -1;
    }
};

int main() {
    Solution solution;

    return 0;
}