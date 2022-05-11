// codeforces: https://codeforces.com/contest/1678/problem/D

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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> col(m, 0);
    vector<int> row(m, 0);
    int las = - n * m;
    int column = 0;
    int rows = 0;
    for (int i = 0; i < n*m; i++) {
        char x;
        cin >> x;
        if (x == '1') {
            las = i;
            if (col[i % m] == 0) {
                col[i % m] = 1;
                column++;
            }
        }
        if (i - las < m) {
            row[i%m]++;
        }
        cout << (row[i%m] + column) << " ";
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
#endif
    fast()

    int testCase = 1;
    cin >> testCase;
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