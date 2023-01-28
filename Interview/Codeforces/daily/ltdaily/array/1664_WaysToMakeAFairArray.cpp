// https://leetcode.cn/problems/ways-to-make-a-fair-array/
// array
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int waysToMakeFair(vector<int> &nums) {
        int sumOdd = 0, sumEven = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i & 1) {
                sumOdd += nums[i];
            } else {
                sumEven += nums[i];
            }
        }
        int ans = 0;
        int curSumOdd = 0, curSumEven = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i & 1) {
                sumOdd -= nums[i];
            } else {
                sumEven -= nums[i];
            }
            if (sumOdd + curSumEven == sumEven + curSumOdd)
                ans++;
            if (i & 1) {
                curSumOdd += nums[i];
            } else {
                curSumEven += nums[i];
            }
        }

        return ans;
    }
};

int main() {
    Solution solution;
    vector<int> test{2, 1, 6, 4};
    cout << solution.waysToMakeFair(test) << endl;

    return 0;
}
