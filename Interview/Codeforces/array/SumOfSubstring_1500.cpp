// codeforces: https://codeforces.com/contest/1691/problem/C

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> arr(n);
    vector<int> onePosition;
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        arr[i] = x - '0';
        if (arr[i] == 1) {
            onePosition.push_back(i);
        }
    }
    int sz = onePosition.size();
    if (sz == 0) {
        cout << 0 << endl;
        return;
    }
    bool removed = false;
    if ((n - 1 - onePosition[sz - 1]) <= k) {
        k -= n - 1 - onePosition[sz - 1];
        onePosition[sz - 1] = n - 1;
        removed = true;
    }
    if ((!removed || sz >= 2) && onePosition[0] <= k) {
        onePosition[0] = 0;
    }

    ll ans = 0;
    for (auto p: onePosition) {
        if (p == 0) {
            ans += 10;
        } else if (p == n - 1) {
            ans += 1;
        } else {
            ans += 11;
        }
    }

    cout << ans << endl;
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