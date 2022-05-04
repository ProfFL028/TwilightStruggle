// codeforces: https://codeforces.com/contest/1674/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    string s, t;
    cin >> s >> t;

    ll ans = 0;
    if (t == "a") {
        ans = 1;
    } else if (t.find("a") != -1) {
        ans = -1;
    } else {
        ans = 1;
        int p = s.length();
        ll tmp = 2;
        while (p) {
            if (p&1) {
                ans = ans * tmp;
            }
            tmp *= tmp;
            p >>= 1;
        }
    }

    cout << ans << endl;
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