// codeforces: https://codeforces.com/contest/1660/problem/A

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n;
    cin >> n;

    ll max1 = 0;
    ll max2 = 0;

    ll x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (max1 < x) {
            max2 = max1;
            max1 = x;
        } else {
            if (max2 < x) {
                max2 = x;
            }
        }
    }
    if (max1 - max2 >= 2) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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