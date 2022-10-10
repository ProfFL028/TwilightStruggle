//  https://leetcode.cn/leetbook/read/top-interview-questions/x2xmre/
#include  <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        sort(nums.begin(), nums.end());
        long long ans = 0;
        long long begin = nums[0];
        bool checked = false;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i-1] + 1) {
                ans = max(ans, 1ll + nums[i-1]-begin);
                begin = nums[i];
                checked = true;
            } else {
                checked = false;
            }
        }
        if (!checked)
            ans = max(ans, 1ll+nums.back() - begin);
        return (int)ans;
    }
};

int main() {
    Solution solution;

    return 0;
}