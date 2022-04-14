// codeforces: https://codeforces.com/contest/1661/problem/D

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int maxLen = 10e6 + 5;
ll arr[maxLen];

void solve() {
    ll n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    ll ans = 0;
    // O(n*K) solution.
//    vector<ll> sum(n, 0);
//    for (int i = n - 1; i >= 0; i--) {
//        ll remain = arr[i] - sum[i];
//        if (remain > 0) {
//            ll dividend = min(k, i + 1ll);
//            ll steps = (remain - 1) / dividend + 1;
//            ans += steps;
//            for (int j = 1; j <= dividend - 1; j++) {
//                sum[i - j] += steps * (dividend - j);
//            }
//        }
//    }
    vector<ll> over(n, 0);
    ll sum = 0;
    ll curr = 0;
    for (int i = n - 1; i >= 0; i--) {
        ll remain = arr[i] - sum;
        if (remain > 0) {
            ll dividend = min(k, i + 1ll);
            ll steps = (remain - 1) / dividend + 1;
            ans += steps;
            sum += steps * dividend;
            curr += steps;
            if (i - k + 1  > 0)
                over[i - k + 1] += steps;
        }
        sum -= curr;
        curr -= over[i];
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