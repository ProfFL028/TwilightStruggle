
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        int endIdx = -1;
        g.resize(n+1);
        depth.resize(n+1, INT_MAX);
        for (int i = 0; i < n; i ++) {
            if (wordList[i]== endWord) {
                endIdx = i+1;
                break;
            }
        }
        if (endIdx == -1) {
            return 0;
        }

        for (int i = 0; i < n; i++) {
            if (canTrans(beginWord, wordList[i])) {
                g[0].push_back(i+1);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (canTrans(wordList[i], wordList[j])) {
                    g[i+1].push_back(j+1);
                    g[j+1].push_back(i+1);
                }
            }
        }
        depth[0] = 0;
        dfs(0);
        return depth[endIdx] == INT_MAX ? 0 : depth[endIdx];
    }
    void dfs(int a) {
        for (auto nxt : g[a]) {
            if (depth[nxt] <= depth[a] + 1) {
                depth[nxt] = depth[a] + 1;
                dfs(nxt);
            }
        }
    }

    bool canTrans(string& s1, string& s2) {
        int diff = 0;
        for (int i = 0; i < s1.length(); i++) {
            diff += (s1[i] == s2[i]);
        }
        return diff == 1;
    }

    vector<vector<int>> g;
    vector<int> depth;
};

int main() {
    Solution s;
    string a = "hit";
    string b =   "cog";
    vector<string> vec = {"hot","dot","dog","lot","log","cog"};

    s.ladderLength(a, b, vec);
    return 0;
}