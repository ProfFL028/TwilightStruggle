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


void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> deg(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<bool> vis(n + 1, false);
    int swaps = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i] && p[i] != i) {
            int v = p[i];
            while (v != i) {
                vis[v] = true;
                swaps++;
                v = p[v];
            }
        }
    }

    int k = n;
    while (k > 0 && deg[k] != n - 1) k--;
    bool bob = p[k] != k && (x ==k || p[k] == x);
    if (k == 0 ||swaps == 0 || p[x] == x && swaps == 1 || !bob && ((swaps % 2 == 0) != (x == k)))
        cout << "Alice\n";
    else
        cout << "Bob\n";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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