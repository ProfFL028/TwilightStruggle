// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/L

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const ll md = 998244353l;
map<pair<int, int>, ll> cmn;

ll per(int m, int n) {
    if (n >= m) {
        return 1;
    }
    pair<int, int> mn(m, n);
    if (cmn.find(mn) != cmn.end()) {
        return cmn[mn];
    } else {
        ll v = 1l;
        for (int i = n + 1; i <= m; i++) {
            v *= i;
            v %= md;
        }
        cmn[mn] = v;
    }
    return cmn[mn];
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    if (k == 0 || b == 0) {
        cout << 1 << endl;
        return;
    }

    ll ans = 1;
    while (k--) {
        for (int i = 1; i <= (a-k); i++) {
            ans += per(b, i);
            ans %= md;
        }
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