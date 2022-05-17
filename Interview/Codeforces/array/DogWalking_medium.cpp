// codeforces: https://codeforces.com/contest/1680/problem/D

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
    ll k;
    cin >> n >> k;
    vector<ll> arr(n);
    for (auto &a: arr) {
        cin >> a;
    }
    ll ans = 0;
    for (int it = 0; it < n; it++) {
        vector<int> zeroCount(n, 0);
        zeroCount[n - 1] = arr[n - 1] == 0;
        for (int i = n - 2; i >= 0; --i) {
            zeroCount[i] = arr[i] == 0;
            zeroCount[i] += zeroCount[i + 1];
        }
        vector<ll> b = arr;
        ll s = accumulate(b.begin(), b.end(), 0ll);
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (b[i] == 0) {
                ll x = i + 1 < n ? zeroCount[i + 1] : 0;
                b[i] = min(k, x * k - s);
                if (b[i] < -k) {
                    ok = false;
                    break;
                }
                s += b[i];
            }
        }
        if (ok) {
            ll pos = 0, mn = 0, mx = 0;
            for (int i = 0; i < n; i++) {
                pos += b[i];
                mn = min(mn, pos);
                mx = max(mx, pos);
            }
            if (pos == 0) {
                ans = max(ans, mx - mn + 1);
            }
        }
        rotate(arr.begin(), arr.begin() + 1, arr.end());
    }
    if (ans == 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
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