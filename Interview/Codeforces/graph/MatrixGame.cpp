//https://codeforces.com/contest/1658/problem/E
// TODO: fix time exclude problem!! x+y, x-y

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

bool descSort(const tuple<ll, ll, ll> &a, const tuple<ll, ll, ll> &b) {
    return get<0>(a) > get<0>(b);
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<tuple<int, int, int>> matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int value;
            cin >> value;
            matrix.emplace_back(value, i, j);
        }
    }
    sort(matrix.begin(), matrix.end(), descSort);
    vector<tuple<int, int>> mWins;
    bool ans[n][n];
    for (auto m : matrix) {
        int x = get<1>(m);
        int y = get<2>(m);
        bool mWin = true;
        for (auto w : mWins) {
            int wx = get<0>(w);
            int wy = get<1>(w);
            if (abs(x - wx) + abs(y - wy) > k) {
                mWin = false;
                break;
            }
        }
        ans[x][y] = mWin;
        if (mWin) {
            mWins.emplace_back(x, y);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (ans[i][j]) {
                cout << "M";
            } else {
                cout << "G";
            }
        }
        cout << endl;
    }
    cout << endl;
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