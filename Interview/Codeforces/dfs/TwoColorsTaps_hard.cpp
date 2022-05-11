// codeforces: https://codeforces.com/contest/1678/problem/E

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
    int n;
    cin >> n;
    vector<int> arr1(n+1, 0), arr2(n+1, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }
    for (int i = 0; i < n;i++) {
        cin >> arr2[i];
    }
    map<int, int> a, b;
    for (int i = 0; i < n; i++) {
        a[arr1[i]] = i;
        b[arr2[i]] = i;
    }

    vector<int> color(n+1, 0);
    ll ans = 0;
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (arr1[i] == arr2[i]) continue;
        int cur = i;
        int cnt = 0;
        while (color[arr1[cur]] == 0) {
            color[arr1[cur]] = 1;
            cnt++;
            cur = a[arr2[cur]];
        }
        c += cnt / 2;
    }
    ans = (ll)c * (n - c) << 1;
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