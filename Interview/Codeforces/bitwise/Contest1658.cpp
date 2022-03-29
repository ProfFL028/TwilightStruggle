//https://codeforces.com/contest/1658/problem/D1


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
    int l, r;
    int x;
    int cnt[20];
    int req[20];
    for (int i = 0; i < 20; i++) {
        cnt[i] = req[i] = 0;
    }
    cin >> l >> r;
    for (int i = l; i <= r; i++) {
        cin >> x;
        for (int j = 0; j < 17; j++) {
            if (x & (1 << j)) {
                cnt[j]++;
            }
        }
    }
    for (int i = 0; i < 17; i++) {
        req[i] = ((((r + 1) >> (i + 1)) << i) + max(((r + 1) % (1 << (i + 1))) - (1 << i), 0))
                 - ((((l + 1) >> (i + 1)) << i) + max(((l + 1) % (1 << (i + 1))) - (1 << i), 0));
    }
    ll ans = 0;
    for (int i = 0; i < 17; i++) {
        if (cnt[i] != req[i]) {
            ans |= 1 << i;
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