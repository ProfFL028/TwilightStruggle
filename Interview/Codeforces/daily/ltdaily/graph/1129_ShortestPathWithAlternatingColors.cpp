// https://leetcode.cn/problems/shortest-path-with-alternating-colors/
// graph, bfs
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges) {
        vector<vector<vector<int>>> g(2, vector<vector<int>>(n));
        for (const auto &edge: redEdges) {
            g[0][edge[0]].push_back(edge[1]);
        }
        for (const auto &edge: blueEdges) {
            g[1][edge[0]].push_back(edge[1]);
        }

        vector<vector<int>> paths(2, vector<int>(n, INT_MAX));
        paths[0][0] = 0;
        paths[1][0] = 0;
        queue<pair<int, int>> q;
        q.push({0, 0});
        q.push({1, 0});

        while (!q.empty()) {
            auto [color, node] = q.front();
            q.pop();
            for (auto nxt : g[1 - color][node]) {
                if (paths[1-color][nxt] == INT_MAX) {
                    paths[1-color][nxt] = paths[color][node] + 1;
                    q.push({1-color, nxt});
                }
            }
        }
        vector<int> answer(n);
        for (int i = 0; i < n; i++) {
            answer[i] = min(paths[0][i], paths[1][i]);
            if (answer[i] == INT_MAX) {
                answer[i] =  -1;
            }
        }

        return answer;
    }
};

int main() {
    Solution solution;

    return 0;
}
