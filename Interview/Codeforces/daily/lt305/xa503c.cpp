#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        n = s.size();
        return findIt(s, wordDict, 0) == n;
    }
    int findIt(string& s, vector<string>& wordDict, int start) const {
        if (start == n)
            return n;

        int reach = start;
        for (auto& word : wordDict) {
            int idx = find(s, word, start);
            if (idx != -1) {
                reach = max(reach, findIt(s, wordDict, idx));
            }
        }
        return reach;
    }
    int find(string& s, string& w, int start) const {
        int k = w.size();
        for (int i = 0; i < k; i++) {
            if (start+i >= n || s[i+start] != w[i])
                return -1;
        }
        return start + k;
    }
    int n;
};

int main() {
    string s = "catsandog";
    vector<string> dict = {"cats","dog","sand","and","cat"};
    Solution solution;
    cout << solution.wordBreak(s, dict) << endl;
    return 0;
}
