// https://leetcode.cn/leetbook/read/top-interview-questions-medium/xvpj16/

#include <iostream>
using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        unordered_map<int,int> x;
        for (auto num : nums) {
            x[num]++;
        }
        if (x[0] >=3) {
            ans.push_back({0,0,0});
        }
        for (auto m : x) {
            if (m.first != 0 && m.second >= 2 && x.count(m.first * -2)) {
                ans.push_back({m.first, m.first, -2 * m.first});
            }
        }

        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        unordered_map<int,int> mp;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            mp[-nums[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            for (int j  = i+1; j < n; j++) {
                int sm = nums[i] + nums[j];
                if (mp[sm] && mp[sm] > j) {
                    ans.push_back({nums[i], nums[j], nums[mp[sm]]});
                }
            }
        }
        return ans;
    }
};
int main() {
    Solution solution;

    return 0;
}