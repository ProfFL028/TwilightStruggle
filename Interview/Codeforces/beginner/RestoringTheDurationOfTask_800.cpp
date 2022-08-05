// codeforces: https://codeforces.com/contest/1690/problem/C

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
    int n;
    cin >> n;
    vector<int> a(n, 0), b(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (auto &x: b) {
        cin >> x;
    }

    cout << b[0] - a[0];
    for (int i = 1; i < n; ++i) {
        if (b[i - 1] > a[i]) {
            cout << " " << b[i] - b[i - 1];
        } else {
            cout << " " << b[i] - a[i];
        }
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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