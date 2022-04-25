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
    if (k == 1) {
        return
    }
    return -1;
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;


    stack<tuple<int, int, int, int>> s;
    map<tuple<int, int, int>, int> dp;

    s.emplace(a, b, k, 1);
    while (!s.empty()) {
        auto x = s.top();
        s.pop();
        tuple<int, int, int> abk = tuple<int, int, int>(get<0>(x), get<1>(x), get<2>(x));
        if (dp.find(abk) == dp.end()) {
            s.push(x);
            ll result = 0;
            bool solved = true;
            int ak = get<0>(x) / get<2>(x);
            for (int i = 0; i <= ak; i++) {
                int ai = get<0>(x) - i * get<2>(x);
                int bi = get<1>(x) - i;
                int ki = get<2>(x) - 1;
                tuple<int, int, int> abki(ai, bi, ki);
                if (dp.find(abki) == dp.end()) {
                    int tmp = simple(ai, bi, ki);
                    if (tmp != -1) {
                        dp[abki] = tmp;
                        result = (result + dp[abki] * C(bi, i)) % M;
                    } else {
                        solved = false;
                        if (i <= get<1>(x)) {
                            s.emplace(ai, bi, ki, C(get<1>(x), i));
                        }
                    }
                }
            }
            if (solved) {
                dp[abk] = result;
                s.pop();
            }
        }
    }

    cout << dp[tuple<int, int, int>(a, b, k)] << endl;
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