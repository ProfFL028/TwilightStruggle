// codeforces: https://codeforces.com/contest/1676/problem/E

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
    int n, q;
    cin >> n >> q;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end(), greater<int>());
    vector<ll> s(n, 0);
    s[0] = arr[0];
    for (int i = 1; i < n; i++) {
        s[i] = arr[i] + s[i-1];
    }
    for (int t = 0; t < q; t++) {
        ll v;
        cin >> v;
        if (s[n - 1] < v) {
            cout << -1 << endl;
            continue;
        }
        int left = 0;
        int right = n;
        int ans = (right - left) / 2 + left;
        while (left < right) {
            if (s[ans] < v) {
                left = ans + 1;
            } else {
                right = ans;
            }
            ans = (right - left) / 2 + left;
        }
        cout << (ans+1) << endl;
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