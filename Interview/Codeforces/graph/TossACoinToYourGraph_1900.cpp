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
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<int> degree(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> vertex[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        degree[b]++;
    }

    if (k == 1) {
        cout << *min_element(vertex.begin()+1, vertex.end()) << endl;
        return;
    }

    auto check = [&](int value) {
        vector<int> d(n + 1);
        vector<bool> visited(n + 1, false);
        vector<int> len(n + 1, 0);

        copy(degree.begin(), degree.end(), d.begin());

        for (int i = 1; i <= n; i++) {
            if (vertex[i] > value) {
                for (auto v: graph[i]) {
                    d[v]--;
                }
            }
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (!d[i] && vertex[i] <= value) {
                q.push(i);
                len[i] = 1;
            }
        }

        int maxL = 0;
        while (q.size() > 0) {
            auto u = q.front();
            q.pop();
            visited[u] = 1;
            for (auto x: graph[u]) {
                if (vertex[x] <= value) {
                    d[x]--;
                    len[x] = max(len[x], len[u] + 1);
                    maxL = max(maxL, len[x]);

                    if (!d[x]) {
                        q.push(x);
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (vertex[i] <= value && !visited[i]) {
                return true;
            }
        }

        return maxL >= k;
    };

    int l = 1, r = INT_MAX;
    while (l < r) {
        int mid = (r - l) / 2 + l;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if (l == INT_MAX) {
        cout << "-1" << endl;
    } else {
        cout << l << endl;
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