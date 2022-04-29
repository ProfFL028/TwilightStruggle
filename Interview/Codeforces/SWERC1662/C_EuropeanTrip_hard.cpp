#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif

using i64 = long long;

const int mod = 998244353;

vector<vector<i64>> operator*(const vector<vector<i64>>& a, const vector<vector<i64>>& b) {
    if (a.empty() || b.empty()) {
        return {{}};
    }
    vector<vector<i64>> c((int) a.size(), vector<i64>((int) b[0].size()));
    for (int i = 0; i < (int) c.size(); ++i) {
        for (int j = 0; j < (int) c[0].size(); ++j) {
            c[i][j] = 0;
            for (int k = 0; k < (int) b.size(); ++k) {
                c[i][j] = (c[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
            }
        }
    }
    return c;
}

vector<vector<i64>> power(vector<vector<i64>> a, int k) {
    vector<vector<i64>> res((int) a.size(), vector<i64>((int) a.size()));
    for (int i = 0; i < (int) a.size(); ++i) {
        res[i][i] = 1;
    }
    for (; k; k /= 2, a = a * a) {
        if (k % 2) res = res * a;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        g[x][y] = g[y][x] = 1;
    }
    vector<vector<i64>> mat(3 * n, vector<i64>(3 * n));
    for (int i = 0; i < n; ++i) {
        (mat[3 * i + 0][3 * i + 1] += 1) % mod;
        (mat[3 * i + 1][3 * i + 2] += 1) % mod;
        (mat[3 * i + 2][3 * i + 1] += 1) % mod;
        for (int j = 0; j < n; ++j) {
            if (g[i][j]) {
                (mat[3 * i + 0][3 * j] += 1) % mod;
                (mat[3 * j + 1][3 * j] -= 1 - mod) % mod;
                (mat[3 * i + 2][3 * j] += 1) % mod;
            }
        }
    }
    vector<vector<i64>> res = power(mat, k);
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + res[3 * i + 0][3 * i + 0]) % mod;
    }
    cout << ans << '\n';
    return (0-0); // <3
}