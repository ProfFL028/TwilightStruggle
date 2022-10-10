// https://leetcode.cn/leetbook/read/top-interview-questions/xafdmc/
#include  <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int longestSubstring(string s, int k) {
        if (s.size() < k) {
            return 0;
        }
        map<char, int> mp;
        for (auto c : s) {
            mp[c]++;
        }
        unordered_set<char> cannt;
        for (auto m : mp) {
            if (m.second < k) {
                cannt.insert(m.first);
            }
        }
        if (cannt.size() == 0) {
            return s.size();
        }
        int ans = 0;
        int lastI = 0;
        for (int i = 0; i < s.size(); i++) {
            if (cannt.find(s[i]) != cannt.end()) {
                ans = max(ans, longestSubstring(s.substr(lastI, i - lastI), k));
                lastI = i+1;
            }
        }
        ans = max(ans, longestSubstring(s.substr(lastI, s.size() - lastI), k));
        return ans;
    }

    int sz(map<char, int>& cur, int k) {
        int sz = 0;
        for (auto m : cur) {
            if (m.second >=k) {
                sz += m.second;
            } else {
                sz = -1;
                break;
            }
        }
        cur.clear();
        return sz;
    }
};

int main() {
    Solution solution;
    cout << solution.longestSubstring("bbaaacbd",3) << endl;
    return 0;
}