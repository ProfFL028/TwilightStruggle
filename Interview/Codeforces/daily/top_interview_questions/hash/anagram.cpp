// https://leetcode.cn/leetbook/read/top-interview-questions-medium/xvaszc/

#include <iostream>

using namespace std;
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string, vector<string>> mp;

        for(auto str : strs) {
            string cpy = str;
            sort(cpy.begin(), cpy.end());
            if (mp.count(cpy)) {
                mp[cpy].push_back(str);
            } else {
                mp[cpy] = {str};
            }
        }

        vector<vector<string>> ans;
        for (auto m : mp) {
            ans.push_back(m.second);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}