// codeforces: https://codeforces.com/contest/1688/problem/D

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
    int n, k;
    cin >> n >> k;
    vector<ll> arr(n+1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i-1];
    }

    if (k >= n) {
        cout << (k - 1ll + k - n) * n / 2 + arr[n]<< endl;
    } else {
        ll mx = arr[k];
        for (int i = k+1; i <= n; i++) {
            mx = max(mx, arr[i] - arr[i-k]);
        }
        cout << mx + (k - 1ll) * k / 2 << endl;
    }

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