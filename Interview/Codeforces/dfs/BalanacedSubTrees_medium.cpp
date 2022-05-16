// codeforces: https://codeforces.com/contest/1676/problem/G

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
    cin >> n;
    vector<set<int>> arr(n + 1);
    int t;
    for (int i = 2; i <= n; i++) {
        cin >> t;
        arr[t].insert(i);
    }
    string s;
    cin >> s;
    vector<pair<int, int>> tree(n + 1);

    function<void(int, int)> dfs = [&](int u, int v) {
        pair<int, int> bw(0, 0);
        for (auto x: arr[u]) {
            if (x == v) continue;
            dfs(x, u);
            bw.first += tree[x].first;
            bw.second += tree[x].second;
        }
        if (s[u - 1] == 'B')
            bw.first++;
        else bw.second++;
        tree[u] = bw;
    };
    dfs(1, -1);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += (tree[i].first == tree[i].second);
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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