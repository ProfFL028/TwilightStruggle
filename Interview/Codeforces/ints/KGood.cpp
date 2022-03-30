// codeforces:  https://codeforces.com/contest/1656/problem/D

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

vector<ll> power2s;

void init() {
    for (int i = 1; i < 64; i++) {
        power2s.push_back(1 << i);
    }
}

void solve() {
    ll n;
    cin >> n;

    ll x = n;
    while (x % 2 == 0) x /= 2;
    if (x == 1) {
        cout << -1 << endl;
        return;
    }
    if (x <= 2e9 && x * (x + 1) <= 2 * n) {
        cout << x << endl;
    } else {
        cout << 2 * n / x << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
#endif
    fast()

    init();

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