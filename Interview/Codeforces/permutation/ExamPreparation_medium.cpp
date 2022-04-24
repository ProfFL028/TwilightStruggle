// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/L

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int M = 998244353;
const int MM = 2 * 10e5 + 2;
vector<int> inv(MM, 0);

int myPower(int x, int y) {
    int result = 1;
    while (y) {
        if (y & 1) {
            result = ll(result) * x % M;
        }
        x = ll(x) * x % M;
        y >>= 1;
    }

    return result;
}

int C(int x, int y) {
    int ans = 1;
    for (int i = x, j = 1; j <= y; i--, j++) {
        if (inv[j] == 0) {
            inv[j] = myPower(j, M - 2);
        }
        ans = (ll) ans * i % M * inv[j] % M;
    }
    return ans;
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    if (k == 0 || b == 0) {
        cout << 1 << endl;
        return;
    }
    if (a <= k) {
        cout << C(a + b, a) << endl;
        return;
    }
    if (a >= (k * b)) {
        cout << myPower(b, k + 1) << endl;
    }

    ll ans = 0;
    vector<vector<vector<int>>> dp(a, vector<vector<int>>(b, vector<int>(k, 1)));
    int ak = a / k;
    for (int i = 0; i< ak; i++) {
        ans +=
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