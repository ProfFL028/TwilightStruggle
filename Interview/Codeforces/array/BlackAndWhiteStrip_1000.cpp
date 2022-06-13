// codeforces: https://codeforces.com/contest/1690/problem/D

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
    vector<int> arr(n+1, 0);
    for (int i = 1; i <= n; i++) {
        char x;
        cin >> x;
        arr[i] = x == 'W';
        arr[i] += arr[i-1];
    }

    int ans = INT_MAX;
    for (int i = k; i <=n; i++) {
        ans = min(ans, arr[i] - arr[i-k]);
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