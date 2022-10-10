// 
#include  <bits/stdc++.h>

using namespace std;
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size();
        n = matrix[0].size();
        dp.resize(m, vector<int>(n, 0));
        ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0;j < n; j++) {
                ans = max(dfs(matrix, i, j), ans);
            }
        }
        return ans;
    }
    int dfs(vector<vector<int>>& matrix, int i, int j) {
        if (dp[i][j] > 0) {
            return dp[i][j];
        }
        dp[i][j]++;
        if (i > 0 && matrix[i-1][j] < matrix[i][j]) {
            dp[i][j] = max(dp[i][j], 1+dfs(matrix, i-1, j));
        }
        if (i < m-1 && matrix[i+1][j] < matrix[i][j]) {
            dp[i][j] = max(dp[i][j], 1+dfs(matrix, i+1, j));
        }
        if (j > 0 && matrix[i][j-1] < matrix[i][j]) {
            dp[i][j] = max(dp[i][j], 1+dfs(matrix, i, j-1));
        }
        if (j < n -1 && matrix[i][j+1] < matrix[i][j]) {
            dp[i][j] = max(dp[i][j], 1+dfs(matrix, i, j+1));
        }
        return dp[i][j];
    }

    int m, n, ans;
    vector<vector<int>> dp;
};

int main() {
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
    Solution solution;
    cout << solution.longestIncreasingPath(matrix) << endl;

    return 0;
}