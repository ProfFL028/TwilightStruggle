// https://leetcode.cn/problems/check-if-matrix-is-x-matrix/
// 
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    /**
     * check elements in diagonals are not equal to zero.
     * check elements that are not in diagonals equal to zero.
     * @param grid
     * @return
     */
    bool checkXMatrix(vector<vector<int>>& grid) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (i == j || (i + j) == (grid.size() - 1)) {
                    if (grid[i][j] == 0) {
                        return false;
                    }
                } else if (grid[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution solution;

    return 0;
}
