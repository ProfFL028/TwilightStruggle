// codeforces: https://codeforces.com/contest/1675/problem/F

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

vector<vector<int>> g;
bool things[200005];
bool onPath[200005];

void dfs(int x, int y) {
    for (auto& t : g[x]) {
        if (t == y) continue;
        dfs(t, x);
        if (things[t]) things[x] = true;
        if (onPath[t]) onPath[x]=true;
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    g.clear();
    g.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        things[i] = false;
        onPath[i] = false;
    }

    int x, y;
    cin >> x >> y;
    for (int i = 0; i < k; i++) {
        int t;
        cin >> t;
        things[t] = true;
    }

    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    onPath[y] = true;
    dfs(x, 0);

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        if (onPath[i]) {
            ans++;
        } else if (things[i]) {
            ans += 2;
        }
    }

    cout << ans - 1 << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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