// codeforces: https://codeforces.com/contest/1690/problem/B

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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    bool isOK = true;
    int diff = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            isOK = false;
            break;
        }
        if (b[i] == 0) {
            isOK = a[i] <= diff;
        } else {
            if (diff == INT_MAX) {
                diff = a[i] - b[i];
            } else {
                isOK = diff == (a[i] - b[i]);
            }
        }
        if (!isOK)
            break;
    }
    cout << (isOK ? "YES" : "NO") << endl;
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