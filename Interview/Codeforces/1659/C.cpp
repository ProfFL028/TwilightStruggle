// codeforces: https://codeforces.com/contest/1659/problem/C

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;


void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> arr(n + 1);
    for (int i = 1; i < n + 1; i++) {
        cin >> arr[i];
    }

    ll ans = arr[1] * b;
    int capital = 0;
    for (int i = 2; i <= n; i++) {
        if (a < (n - i + 1) * b) { // it may cause int overflow problem!!!
            ans += a * (arr[i - 1] - arr[capital]);
            capital = i - 1;
        }
        ans += (arr[i] - arr[capital]) * b;
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