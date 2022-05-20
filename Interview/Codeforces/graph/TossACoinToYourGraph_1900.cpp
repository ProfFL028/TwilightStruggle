// codeforces: https://codeforces.com/contest/1679/problem/D
// graph, dfs, binary search

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
    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<int> vertex(n + 1);
    map<int, set<int>> mp;
    vector<vector<int>> g(n + 1, vector<int>());
    set<int, less<>> v;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        vertex[i] = x;
        v.insert(x);
        mp[x].insert(i);
    }
    vector<int> du(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        du[b]++;
    }
    vector<int> values;
    for (auto x: v) {
        values.push_back(x);
    }

    auto check = [&](int p, int pp, int d, int mx) {
        for (auto cur: g[p]) {
            if (vertex[cur] == pp) continue;
            if (vertex[cur] > mx) return false;
        }
        return false;
    };

    int l = 0, r = values.size();
    int ans = -1;
    while (l <= r) {
        int mid = (r - l) / 2 + l;
        ans = values[mid];
        for (auto p: mp[ans]) {

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