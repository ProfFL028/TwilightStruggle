#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int reachableNodes(int n, vector<vector<int>>& edges, vector<int>& restricted) {
        vector<vector<int>> g(n);
        set<int> cannotAccess;
        for (auto & r : restricted) {
            cannotAccess.insert(r);
        }
        for (auto& edge: edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        queue<pair<int, int>> q;
        q.push(make_pair(0, 0));
        int ans = 1;
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            for (auto& cur : g[p.first]) {
                if (cur != p.first && cur != p.second && cannotAccess.find(cur) == cannotAccess.end()) {
                    q.push(make_pair(cur, p.first));
                    ans++;
                }
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> edges = {{0,1}, {1,2},{3,1}, {4,0},{0,5},{5,6}};
    vector<int> restricted;
    restricted.push_back(4);
    restricted.push_back(5);
    Solution solution;
    cout << solution.reachableNodes(7, edges, restricted);

    return 0;
}