// https://leetcode.cn/leetbook/read/top-interview-questions/x2muyh/
#include  <bits/stdc++.h>

using namespace std;
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(numCourses, vector<int>());
        vector<int> deg(numCourses);
        for (auto pre : prerequisites) {
            g[pre[0]].push_back(pre[1]);
            deg[pre[1]]++;
        }
        bool found = true;
        while (found) {
            found = false;
            for (int i = 0; i < numCourses; i++) {
                if (deg[i] == 0) {
                    for (int k = g[i].size() - 1; k>=0; k--) {
                        deg[g[i][k]]--;
                        g[i].pop_back();
                        found = true;
                    }
                }
            }
        }
        for (auto d : deg) {
            if (d > 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution solution;

    return 0;
}