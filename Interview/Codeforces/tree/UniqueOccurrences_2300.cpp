// codeforces: https://codeforces.com/contest/1681/problem/F
// TODO: speed up.
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
    vector<vector<pair<int,int>>> graph(n+1);
    vector<vector<pair<int, int>>> color(n+1);
    for (int i = 1; i < n; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        graph[u].emplace_back(v, x);
        graph[v].emplace_back(u, x);
        color[x].emplace_back(u, v);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        auto c = color[i];
        if (c.size() > 0) {
            for (auto pi : c) {
                queue<pair<int, int>> q;
                q.push(make_pair(pi.first, pi.second));
                ll left = 0;
                ans++;
                while (!q.empty()) {
                    auto cur = q.front();
                    q.pop();
                    for (auto next : graph[cur.first]) {
                        if (next.second != i && next.first != cur.second) {
                            ans++;
                            left++;
                            q.push(make_pair(next.first, cur.first));
                        }
                    }
                }
                q.push(make_pair(pi.second, pi.first));
                ll right = 0;
                while (!q.empty()) {
                    auto cur = q.front();
                    q.pop();
                    for (auto next : graph[cur.first]) {
                        if (next.second != i && next.first != cur.second) {
                            ans++;
                            right++;
                            q.push(make_pair(next.first, cur.first));
                        }
                    }
                }
                ans += left * right;
            }
        }
    }
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