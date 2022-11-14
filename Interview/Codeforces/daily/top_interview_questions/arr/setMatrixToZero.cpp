//https://leetcode.cn/leetbook/read/top-interview-questions-medium/xvmy42/

#include<iostream>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<int> rows, cols;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                if (matrix[i][j] == 0) {
                    rows.push_back(i);
                    cols.push_back(j);
                }
            }
        }
        for (auto i : rows) {
            for (int j = 0; j < matrix[0].size(); j++) {
                matrix[i][j] = 0;
            }
        }

        for (auto j: cols) {
            for (int i = 0; i < matrix.size(); i++) {
                matrix[i][j] = 0;
            }
        }
    }
};

int main() {
    Solution solution;
}
