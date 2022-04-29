// codeforces: https://codeforces.com/contest/1662/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const ll M = 998244353;


vector<vector<ll>> operator*(const vector<vector<ll>> &a, const vector<vector<ll>> &b) {
    if (a.empty() || b.empty()) {
        return {{}};
    }
    vector<vector<ll>> c((int) a.size(), vector<ll>((int) b[0].size()));
    for (int i = 0; i < (int) c.size(); ++i) {
        for (int j = 0; j < (int) c[0].size(); ++j) {
            c[i][j] = 0;
            for (int k = 0; k < (int) b.size(); ++k) {
                c[i][j] = (c[i][j] + (a[i][k] * b[k][j]) % M) % M;
            }
        }
    }
    return c;
}

vector<vector<ll>> power(vector<vector<ll>> a, int k) {
    vector<vector<ll>> res((int) a.size(), vector<ll>((int) a.size()));
    for (int i = 0; i < (int) a.size(); ++i) {
        res[i][i] = 1;
    }
    for (; k; k /= 2, a = a * a) {
        if (k % 2) res = res * a;
    }
    return res;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        graph[a][b] = graph[b][a] = 1;
    }
    vector<vector<ll>> mat(3 * n, vector<ll>(3 * n, 0));
    for (int i = 0; i < n; i++) {
        mat[3 * i + 0][3 * i + 1] = (mat[3 * i + 0][3 * i + 1] + 1) % M;
        mat[3 * i + 1][3 * i + 2] = (mat[3 * i + 1][3 * i + 2] + 1) % M;
        mat[3 * i + 2][3 * i + 1] = (mat[3 * i + 2][3 * i + 1] + 1) % M;
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) {
                mat[3 * i + 0][3 * j] = (mat[3 * i + 0][3 * j] + 1) % M;
                mat[3 * j + 1][3 * j] = (mat[3 * j + 1][3 * j] + M - 1) % M; // count-- when using same line.
                mat[3 * i + 2][3 * j] = (mat[3 * i + 2][3 * j] + 1) % M;
            }
        }
    }
    // mat^k
    vector<vector<ll>> powerK = power(mat, k); // mat[a, b]=k means there's a way from a to b within k vertex.
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + powerK[3 * i][3 * i]) % M;
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
#endif
    fast()

    int testCase = 1;
    // cin >> testCase;
    while (testCase > 0) {
        solve();
        testCase--;
    }

#ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed : " << 1000 * (lld) clock() / (lld) CLOCKS_PER_SEC
         << " ms\n";
#endif
    return 0;
}