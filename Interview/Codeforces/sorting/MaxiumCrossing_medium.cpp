// codeforces: https://codeforces.com/contest/1676/problem/H2

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
int a[200008];
int n, tmp;

void add(int x) {
    while (x <= n) {
        a[x]++;
        x += x & -x;
    }
}

int get(int x) {
    int ret = 0;
    while (x) {
        ret += a[x];
        x -= x & -x;
    }
    return ret;
}

void solve() {
    memset(a, 0, sizeof a);
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        ans += i - get(tmp - 1);
        add(tmp);
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