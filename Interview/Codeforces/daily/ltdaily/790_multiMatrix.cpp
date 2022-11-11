#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;
class Solution {
public:
    vector<vector<long long>> mulMatrix(const vector<vector<long long>> &m1, const vector<vector<long long>> &m2) {
        int n1 = m1.size(), n2 = m2.size(), n3 = m2[0].size();
        vector<vector<long long>> res(n1, vector<long long>(n3));
        for (int i = 0; i < n1; i++) {
            for (int k = 0; k < n3; k++) {
                for (int j = 0; j < n2; j++) {
                    res[i][k] = (res[i][k] + m1[i][j] * m2[j][k]) % mod;
                }
            }
        }
        return res;
    }

    int numTilings(int n) {
        vector<vector<long long>> mat = {
                {0, 0, 0, 1},
                {1, 0, 1, 0},
                {1, 1, 0, 0},
                {1, 1, 1, 1}
        };
        vector<vector<long long>> matn = {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
        };
        while (n) {
            if (n & 1) {
                matn = mulMatrix(matn, mat);
            }
            mat = mulMatrix(mat, mat);
            n >>= 1;
        }
        return matn[3][3];
    }
};

int main() {
    Solution solution;

    return 0;
}