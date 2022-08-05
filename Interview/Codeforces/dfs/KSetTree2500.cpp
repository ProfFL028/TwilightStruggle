// codeforces:  https://codeforces.com/contest/1691/problem/F

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

const ll M = 1e9 + 7;
const ll MM = 2e5 + 5;
vector<ll> inv(MM, 0);

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
    if (x < 0 || y < 0 || x < y) {
        return 0;
    }
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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<ll> sz(n + 1, 0), cnt(n+1), cntSz(n+1);

    ll ans = 0, curAns = 0;
    function<void(int, int)> dfs1 = [&](int v, int p) {
        ll sub = 0;
        sz[v] = 1;
        for (auto u: graph[v]) {
            if (u != p) {
                dfs1(u, v);
                sz[v] += sz[u];
                sub = (sub + C(sz[u], k) + MOD) % MOD;
            }
        }

        cnt[v] = (C(sz[v], k) - sub + MOD) % MOD;
        cntSz[v] = (cnt[v] * sz[v]) % MOD;
        curAns = (curAns + cntSz[v]) % MOD;
    };
    dfs1(1, 1);

    function<void(int, int)> dfs2 = [&](int v, int p) {
        ans = (ans + curAns) % MOD;
        for (auto u: graph[v]) {
            if (u != p) {
                // store
                int store_v_sz = sz[v];
                ll store_v_cnt = cnt[v];
                ll store_v_cntSz = cntSz[v];
                int store_u_sz = sz[u];
                ll store_u_cnt = cnt[u];
                ll store_u_cntSz = cntSz[u];
                ll store_curAns = curAns;

                // recalculate size[v], size[u]
                sz[v] -= sz[u];
                sz[u] = sz.size()-1;

                // recalculate cnt[v]
                cnt[v] = (cnt[v] - C(store_v_sz, k) + MOD) % MOD;
                cnt[v] = (cnt[v] + C(sz[v], k)) % MOD;
                cnt[v] = (cnt[v] + C(store_u_sz, k)) % MOD;

                // recalculate cnt[u]
                cnt[u] = (cnt[u] - C(store_u_sz, k) + MOD) % MOD;
                cnt[u] = (cnt[u] + C(sz[u], k)) % MOD;
                cnt[u] = (cnt[u] - C(sz[v], k) + MOD) % MOD;

                // recalculate cntSz
                cntSz[v] = (cnt[v] * sz[v]) % MOD;
                cntSz[u] = (cnt[u] * sz[u]) % MOD;

                // recalculate curAns
                curAns = (curAns - store_v_cntSz - store_u_cntSz + MOD + MOD) % MOD;
                curAns = (curAns + cntSz[v] + cntSz[u]) % MOD;

                dfs2(u, v);

                // restore
                sz[v] = store_v_sz;
                cnt[v] = store_v_cnt;
                cntSz[v] = store_v_cntSz;
                sz[u] = store_u_sz;
                cnt[u] = store_u_cnt;
                cntSz[u] = store_u_cntSz;
                curAns = store_curAns;
            }
        }
    };
    dfs2(1, 1);

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