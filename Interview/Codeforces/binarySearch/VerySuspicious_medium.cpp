// codeforces: https://codeforces.com/contest/1670/problem/D

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

ll intersectionCount(ll x) {
    ll t = x / 3;
    ll result = t * t * 3;
    ll extra = t * 2;
    if (x % 3 == 1)
        result += extra;
    else if (x % 3 == 2)
        result += extra + extra + 1;

    return  result;
}

void solve() {
    ll n;
    cin >> n;
    ll ans = 0;
    ll left = 1, right=1e8;
    while (left <= right) {
        ll mid = (right-left) / 2 + left;
        ll y = intersectionCount(mid) * 2;
        if (y >= n) {
            ans = mid;
            right = mid-1;
        } else {
            left = mid + 1;
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