// codeforces: https://codeforces.com/contest/1679/problem/F


#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 998244353;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(10, vector<int>(10, 0));
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[min(a, b)][max(a, b)] = 1;
    }
    vector<vector<int>> dp(n + 1, vector<int>(1025, 0));
    for (int i = 0; i < 10; i++) {
        dp[1][1 << i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < 1024; j++) {
            vector<int> l(10, 0);
            for (int s = 0; s < 10; s++) {
                if (j & (1 << s))
                    l[s] = 1;
            }
            for (int k = 0; k < 10; k++) {
                bool canAdd = true;
                for (int s = 0; s <10; s++) {
                    if (l[s] && g[s][k]) {
                        canAdd = false;
                        break;
                    }
                }
                if (canAdd) {
                    if (dp[i][j | (1 << k)] + dp[i - 1][j] < MOD) {
                        dp[i][j | (1 << k)] = dp[i - 1][j] + dp[i][j | (1 << k)];
                    } else {
                        dp[i][j | (1 << k)] = dp[i - 1][j] - MOD + dp[i][j | (1 << k)];
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < 1024; i++) {
        if (ans + dp[n][i] >= MOD) {
            ans = dp[n][i] - MOD + ans;
        } else {
            ans += dp[n][i];
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