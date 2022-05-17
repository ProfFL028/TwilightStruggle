// codeforces: https://codeforces.com/contest/1680/problem/E

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
    vector<char> up(n), down(n);
    for (auto &x: up) cin >> x;
    for (auto &x: down) cin >> x;
    vector<vector<int>> dp(2, vector<int>(n, 0));
    int r = n - 1;
    for (; r >= 0; --r) {
        if (up[r] == '*' || down[r] == '*') break;
    }
    int l = 0;
    for (; l <= r; ++l) {
        if (up[l] == '*' || down[l] == '*') break;
    }
    dp[0][l] = up[l] == '.';
    dp[1][l] = down[l] == '.';
    if (up[l] == '*' && down[l] == '*') {
        dp[0][l] = dp[1][l] = 1;
    }
    for (int i = l + 1; i <= r; i++) {
        if (up[i] == '*' && down[i] == '*') {
            dp[0][i] = min(dp[0][i - 1], dp[1][i - 1]) + 2;
            dp[1][i] = dp[0][i];
        } else if (up[i] == '*' && down[i] == '.') {
            dp[0][i] = min(dp[0][i - 1] + 1, dp[1][i - 1] + 2);
            dp[1][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 2);
        } else if (up[i] == '.' && down[i] == '*') {
            dp[0][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 2);
            dp[1][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 1);
        } else {
            dp[0][i] = min(dp[0][i - 1] + 1, dp[1][i - 1] + 2);
            dp[1][i] = min(dp[0][i - 1] + 2, dp[1][i - 1] + 1);
        }
    }
    int ans = min(dp[0][r], dp[1][r]);
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