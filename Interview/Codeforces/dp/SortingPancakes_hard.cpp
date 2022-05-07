// codeforces: https://codeforces.com/contest/1675/problem/G

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

const int maxN = 255;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
    }
    vector<vector<vector<ll>>> dp(maxN, vector<vector<ll>>(maxN, vector<ll>(maxN, INT_MAX)));

    dp[0][0][m] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            ll curMin = INT_MAX;
            for (int k = m-j+1; k<=m; k++) curMin = min(curMin, dp[i-1][j][k]);
            for (int k = m-j; k>=0; k--) {
                curMin = min(curMin, dp[i-1][j][k]);
                dp[i][j+k][k] = curMin + abs(arr[i] - j - k);
            }
        }
    }
    ll ans = INT_MAX;
    for (int i = 0; i <= m; i++) {
        ans = min(ans, dp[n][m][i]);
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
#endif
    fast()

    int testCase = 1;
    //cin >> testCase;
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