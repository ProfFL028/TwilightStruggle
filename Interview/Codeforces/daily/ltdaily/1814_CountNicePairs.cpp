// https://leetcode.cn/problems/count-nice-pairs-in-an-array/
// array, enumeration
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countNicePairs(vector<int> &nums) {
        const int M = 1e9+7;
        int ans = 0;
        unordered_map<int, int> cnt;
        for (auto &n: nums) {
            int rn = reverseInt(n);
            int diff = rn - n;
            ans = (ans + cnt[diff]) % M;
            cnt[diff]++;
        }
        return ans;
    }

    static int reverseInt(int n) {
        string sn = to_string(n);
        reverse(sn.begin(), sn.end());
        return atoi(sn.c_str());
    }
};

int main() {
    Solution solution;
    vector<int> vec1{5, 12, 31};
    vector<int> vec2{42,11,1,97};
    cout << solution.countNicePairs(vec1) << "\n";
    cout << solution.countNicePairs(vec2) << "\n";
    return 0;
}
