// codeforces: https://codeforces.com/contest/1681/problem/D

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
    ll x;
    cin >> n >> x;

    queue<ll> q;
    map<ll, int> v;
    v[x] = 0;
    q.push(x);
    int ans = INT_MAX;
    while (!q.empty()) {
        ll cur = q.front();
        q.pop();
        string s = to_string(cur);
        if (s.length() >= n) {
            ans = min(ans, v[cur]);
        } else {
            for (auto i : s) {
                if (i != '0' && i != '1') {
                    ll w = cur * (i - '0');
                    if (!v[w]) {
                        v[w] = v[cur] + 1;
                        q.push(w);
                    } else {
                        if (v[w] > v[cur] + 1) {
                            v[w] = v[cur] + 1;
                            q.push(w);
                        }
                    }
                }
            }
        }
    }
    if (ans != INT_MAX) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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