#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        // return search(matrix, target, 0, n - 1, 0, m - 1);
    }

    bool search(vector<vector<int>> &matrix, int target, int left, int right, int top, int down) {
        if (left > right) return false;
        if (top > down) return false;
        if (right >= matrix[0].size()) return false;
        if (down >= matrix.size()) return false;
        int length = right - left + 1;
        int height = down - top + 1;
        if (matrix[top][left] > target) return false;
        if (matrix[down][right] < target) return false;

        if (length == 1) {
            int m = top + (down - top) / 2;
            while (top <= down) {
                if (matrix[m][left] == target) return true;
                if (matrix[m][left] > target) {
                    down = m - 1;
                } else {
                    top= m + 1;
                }
                m = top + (down - top) / 2;
            }
            return false;
        }
        if (height == 1) {
            int m = left + (right - left) / 2;
            while (left <= right) {
                if (matrix[top][m] == target) return true;
                if (matrix[top][m] > target) right = m - 1;
                else left = m + 1;
                m = left + (right - left) / 2;
            }
            return false;
        }

        int c = min(length, height)-1;
        int cl = 0, cr= c;
        int cm = cl + (cr - cl) / 2;
        while (cl <= cr) {
            if (matrix[top+cm][left + cm] == target) {
                return true;
            } else if (matrix[top +cm][left + cm] > target) {
                cr = cm - 1;
            } else {
                cl = cm + 1;
            }
            cm = cl + (cr - cl) /2;
        }
        bool ans = search(matrix, target, left + cl, right, top, top+ cl - 1);
        if (ans) return true;
        ans = search(matrix, target, left, left + cr, top + cr + 1, down);
        if (ans) return true;
        if (length > height) {
            ans = search(matrix, target, left + height, right, top, down);
        } else if (length < height) {
            ans = search(matrix, target, left, right, top + length, down);
        }

        return ans;
    }

};

int main() {
    Solution solution;
    vector<vector<int>> nums{{4,6,9,10,15},{9,12,13,15,16}};
    int target = 14;

    cout << solution.searchMatrix(nums, target) << endl;
    return 0;
}