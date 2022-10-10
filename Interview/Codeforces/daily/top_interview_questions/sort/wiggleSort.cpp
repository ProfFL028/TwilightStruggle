/**
https://leetcode.cn/leetbook/read/top-interview-questions/xaygd7/
 */
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void wiggleSort(vector<int> &nums) {
        vector<int> cpy(nums);
        sort(cpy.begin(), cpy.end());
        int n = nums.size();
        for (int i = 0; i < n / 2; i++) {
            nums[2 * i] = cpy[(n - 1) / 2 - i];
            nums[2 * i + 1] = cpy[n - i - 1];
        }
        if (n % 2) {
            nums[n - 1] = cpy[0];
        }
    }
};

int main() {
    vector<int> nums{1, 1, 1, 4, 5, 6};
    Solution solution;
    solution.wiggleSort(nums);

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}