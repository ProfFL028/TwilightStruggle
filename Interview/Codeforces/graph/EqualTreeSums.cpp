// codeforces: https://codeforces.com/contest/1656/problem/E

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int maxLen = 10e6 + 5;


void solve() {
    int n;
    cin >> n;

    vector<int> graph[n + 1];
    int depth[n + 1];
    memset(depth, 0, sizeof(int) * (n+1));

    // store the graph in two dimension array.
    for (int i = 0; i < n-1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    // calc node depth
    stack<int> visit;
    visit.push(1);
    depth[1] = 1;
    while (!visit.empty()) {
        int cur = visit.top();
        visit.pop();
        for (auto v: graph[cur]) {
            if (depth[v] == 0) {
                visit.push(v);
                depth[v] = depth[cur] + 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int ans = graph[i].size() * ((depth[i] % 2 == 0) ? 1 : -1);
        cout << ans << " ";
    }
    cout << endl;
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