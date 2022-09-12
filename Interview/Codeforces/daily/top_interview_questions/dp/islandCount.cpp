// https://leetcode.cn/leetbook/read/top-interview-questions/x2p3cd/
#include  <bits/stdc++.h>

using namespace std;

class DSU {
public:
    DSU(int sz) {
        nodes.resize(sz);
        visited.resize(sz, false);
        for (int i = 0; i < sz;i++) {
            nodes[i] = i;
        }
        diff = sz;
    }
    void disable(int p) {
        nodes[p] = -1;
        diff--;
        visited[p] = true;
    }
    void connect(int a, int b) {
        int pa = parent(a), pb = parent(b);
        if (pa == pb) {
            return ;
        }
        if (pa > pb) {
            connect(pb, pa);
            return ;
        }
        nodes[pb] = nodes[pa];
        diff--;
    }
    int parent(int x) {
        if (x < 0 || x >= nodes.size())
            return -1;
        if (nodes[x] == x) return x;
        return parent(nodes[x]);
    }
    vector<int> nodes;
    vector<bool> visited;
    int diff;
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        DSU dsu(m * n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dsu.visited[i * n + j] = true;
                if (grid[i][j] == '0') {
                    dsu.disable(i *n + j);
                } else {
                    connect(grid, dsu,i, j);
                }
            }
        }
        return dsu.diff;
    }

    void connect(vector<vector<char>>& grid, DSU& dsu, int i, int j) {
        if (i>0 && grid[i-1][j] == '1') {
            dsu.connect((i-1)* n + j, i*n +j);
            if (!dsu.visited[(i-1)* n + j]) {
                dsu.visited[(i-1)* n + j] = true;
                connect(grid, dsu, i - 1, j);
            }
        }
        if (j > 0 && grid[i][j-1] == '1') {
            dsu.connect(i*n + j - 1, i*n+j);
            if (!dsu.visited[i* n + j-1]) {
                dsu.visited[i * n + j-1] = true;
                connect(grid, dsu, i, j - 1);
            }
        }

        if (i< m - 1 && grid[i+1][j] == '1') {
            dsu.connect((i+1)* n + j, i*n +j);
            if (!dsu.visited[(i+1)* n + j]) {
                dsu.visited[(i + 1) * n + j] = true;
                connect(grid, dsu, i + 1, j);
            }
        }
        if (j < n - 1 && grid[i][j+1] == '1') {
            dsu.connect(i*n + j + 1, i*n+j);
            if (!dsu.visited[i* n + j+1]) {
                dsu.visited[i * n + j+1] = true;
                connect(grid, dsu, i, j + 1);
            }
        }
    }
    int m, n;
};
int main() {
    vector<vector<char>> island{{'1','1','1'},{'0','1','0'},{'1','1','1'}};
    Solution solution;
    cout << solution.numIslands(island) << endl;
    return 0;
}