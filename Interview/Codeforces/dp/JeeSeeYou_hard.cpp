// codeforces: https://codeforces.com/contest/1670/problem/F
// TODO: fix ll problem.
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


const int MM = 2 * 10e5 + 2;
vector<int> inv(MM, 0);

int myPower(int x, int y) {
    int result = 1;
    while (y) {
        if (y & 1) {
            result = ll(result) * x % MOD;
        }
        x = ll(x) * x % MOD;
        y >>= 1;
    }

    return result;
}

int C(int x, int y) {
    if (y == 0) {
        return 1;
    }
    int ans = 1;
    for (int i = x, j = 1; j <= y; i--, j++) {
        if (inv[j] == 0) {
            inv[j] = myPower(j, MOD - 2);
        }
        ans = (ll) ans * i % MOD * inv[j] % MOD;
    }
    return ans;
}

void solve() {
    int n;
    ll l, r, z;
    cin >> n >> l >> r >> z;

    function<int(ll, int)> f = [&](ll total, int b) {
        if (b == -1) {
            return 1;
        }
        if (total == 0) {
            return 0;
        }
        int ans = 0;
        int k = total / (1 << b);
        int required = (z >> b) & 1;
        for (int i = required; i <= min(k, n); i += 2) {
            ans = ((C(n, i) * f(total - i * (1 << b), b-1) % MOD) + ans) % MOD;
        }
        return ans;
    };
    int fl = f(l-1, 30);
    int fr = f(r, 30);
    int ans = fr - fl;
    if (ans < 0)
        ans+= MOD;

    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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