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
    ll l, r, a;
    cin >> l >> r >> a;
    if (l / a < r / a) {
        cout << max(r / a + r % a, (r / a - 1 + a - 1)) << endl;
    } else {
        cout << r / a + r % a << endl;
    }

}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_divAndMod.txt", "r", stdin);
    freopen("../data/output_divAndMod.txt", "w", stdout);
    freopen("../data/error_divAndMod.txt", "w", stderr);
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