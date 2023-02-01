// https://leetcode.cn/problems/decode-the-message/
// 
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    string decodeMessage(string key, string message) {
        string ans;
        unordered_map<int, int> mp;
        char cur = 'a';
        for(auto& c : key) {
            if(c != ' ' && mp.find(c) == mp.end()) {
                mp[c] = cur;
                cur++;
            }
        }

        for (auto& c : message) {
            if (c == ' ') {
                ans += c;
            } else {
                ans += mp[c];
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;

    return 0;
}
