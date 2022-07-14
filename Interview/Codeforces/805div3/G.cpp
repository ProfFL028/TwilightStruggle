// codeforces:

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

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> depth(n + 1, 0);
    vector<vector<int>> up(n + 1, vector<int>(n + 1, 0));
    queue<pair<int, int>> q;
    q.push(make_pair(1, 1));
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        depth[cur.first] = depth[cur.second] + 1;
        up[cur.first][0] = cur.second;
        for (int i = 1; i <= n; i++) {
            up[cur.first][i] = up[up[cur.second][i - 1]][i - 1];
        }
        for (auto next: g[cur.first]) {
            if (next != cur.second) {
                q.push(make_pair(next, cur.first));
            }
        }
    }

    auto lca = [&](int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = n; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                u = up[u][i];
            }
        }
        for (int i = n; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return u == v ? u : up[u][0];
    };

    int query;
    cin >> query;
    while (query--) {
        int k;
        cin >> k;
        vector<int> p(k);
        for (auto &x: p) {
            cin >> x;
        }
        sort(p.begin(), p.end(), [depth](int a, int b) {
            return depth[a] > depth[b];
        });

        vector<bool> used(k, false);
        for (int i = 0; i < k; i++) {
            used[i] = lca(p[0], p[i]) == p[i];
        }
        int f = 0;
        while (f < k && used[f]) f++;
        if (f == k) {
            cout << "YES" << endl;
            continue;
        }

        bool ans = true;
        for (int i = f; i < k; i++) {
            if (lca(p[f], p[i]) == p[i])
                used[i]  = true;
        }
        for (auto u : used)  {
            ans &= u;
        }
        ans &= depth[lca(p[0], p[f])] <= depth[p.back()];
        if (ans) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

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