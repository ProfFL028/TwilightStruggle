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

int simple(int a, int b, int k) {
    if (k == 0 || b == 0 || a == 0) {
        return 1;
    }
    if (a <= k) {
        return C(a + b, a);
    }
    if (a >= (k * b)) {
        return myPower(b, k + 1);
    }
    return -1;
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;


    ll ans = 0;
    stack<tuple<int, int, int, int>> s;
    map<tuple<int, int, int>, int> dp;

    s.emplace(a, b, k, 1);
    while (!s.empty()) {
        auto x = s.top();
        s.pop();
        tuple<int, int, int> abk = tuple<int, int, int>(get<0>(x), get<1>(x), get<2>(x));
        if (dp.find(abk) != dp.end()) {
            ans += dp[abk] * get<3>(x) % M;
        } else {
            s.push(x);
            int ak = get<0>(x) / get<2>(x);
            for (int i = 0; i <= ak; i++) {
                int ai = a - i * k;
                int bi = b - i;
                int ki = k - 1;      
                tuple<int, int, int> abki(ai, bi, ki);
                int tmp = simple(ai, bi, ki);
                if (tmp != -1) {
                    dp[abki] = tmp;
                } else {
                    if (i <= b) {
                        s.emplace(ai, bi, ki, C(b, i));
                    }
                }
            }
        }
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