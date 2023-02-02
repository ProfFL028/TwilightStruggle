// leetcode: https://leetcode.cn/problems/partition-array-into-disjoint-intervals/submissions/

#include <bit/stdc++.h>

using namespace std;

class Solution {
public:
    int partitionDisjoint(vector<int> &nums) {
        int n = nums.size();
        int leftMax = nums[0], leftPos = 0, curMax = nums[0];
        for (int i = 1; i < n - 1; i++) {
            curMax = max(curMax, nums[i]);
            if (nums[i] < leftMax) {
                leftMax = curMax;
                leftPos = i;
            }
        }
        return leftPos + 1;
    }
};

int main() {
    Solution solution;

    float f1 = 0x10.1p10;
    cout << f1 << endl;

    return 0;
}