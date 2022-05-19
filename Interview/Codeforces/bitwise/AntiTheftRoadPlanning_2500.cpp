// codeforces: https://codeforces.com/contest/1673/problem/F
// bitwise, gray code,

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 1e9 + 7;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

const int N = 32;

int maxPower2(int x) {
    int res = 1;
    while (x % 2 == 0) {
        res *= 2;
        x /= 2;
    }
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;
    int h[N][N - 1];
    for (int i = 0; i < N; i++) {
        for (int j = 1; j <= N - 1; j++) {
            h[i][j - 1] = maxPower2(j) * maxPower2(j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cout << h[i][j] << " ";
        }
        cout << endl;
    }
    int v[N - 1][N];
    for (int i = 1; i <= N - 1; i++) {
        for (int j = 0; j < N; j++) {
            v[i - 1][j] = 2 * maxPower2(i) * maxPower2(i);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    int b[n][n];
    b[0][0] = 0;
    for (int j = 1; j < n; j++) {
        b[0][j] = b[0][j - 1] ^ h[0][j - 1];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = b[i - 1][j] ^ v[i - 1][j];
        }
    }
    map<int, pair<int, int> > m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[b[i][j]] = {i, j};
        }
    }
    int y = 0;
    while (k--) {
        int x;
        cin >> x;
        pair<int, int> ans = m[x ^ y];
        cout << ans.first + 1 << " " << ans.second + 1 << endl;
        y ^= x;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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