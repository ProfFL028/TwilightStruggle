// https://codeforces.com/contest/1713/problem/D

#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;

int n, a[N][N];

int par[N];
int getPar(int u) {
    if (u < 0) return -getPar(-u);
    if (u == par[u]) return u;
    return par[u] = getPar(par[u]);
}
void join(int u, int v) {
    u = getPar(u); v = getPar(v);
    if (abs(u) != abs(v)) {
        if (u > 0) par[u] = v;
        else par[-u] = -v;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
#endif
    cin.tie(nullptr) -> sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }

        iota(par + 1, par + n + 1, 1);
        // set par[i] == i for i in [1, n]

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (a[i][j] < a[j][i]) join(i, j);
                if (a[i][j] > a[j][i]) join(i, -j);
            }

        for (int i = 1; i <= n; i++) {
            if (getPar(i) < 0) continue;
            // we only perform the operation
            // if and only if getPar(i) > 0
            for (int j = 1; j <= n; j++)
                swap(a[i][j], a[j][i]);
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << a[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}
