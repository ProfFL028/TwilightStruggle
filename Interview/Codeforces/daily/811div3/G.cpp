// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

struct node {
    int x, y;
    int depth;
};


void solve() {
    int n;
    cin >> n;
    vector<node> arr(n + 1, {0, 0, 0});
    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    vector<vector<int>> parentPath(n + 1);
    parent[1] = 0;
    for (int i = 2; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        children[a].push_back(i);
        parent[i] = a;
        arr[i] = {b, c, 0};
    }

    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (auto cur: children[p]) {
            arr[cur].x += arr[p].x;
            arr[cur].y += arr[p].y;
            arr[cur].depth = arr[p].depth + 1;
            parentPath[cur] = parentPath[p];
            parentPath[cur].push_back(p);

            q.push(cur);
        }
    }

    vector<int> path;
    vector<int> ans(n + 1);
    function<void(int)> dfs = [&](int x) {
        path.push_back(x);
        int l = 0;
        int r = path.size() - 1;
        int mid = (l + r) / 2;
        while (l < r) {
            if (arr[x].x >= arr[path[mid]].y) {
                l = mid;
                mid = (l + r + 1) / 2;
            } else {
                r = mid - 1;
                mid = (l + r) / 2;
            }
        }
        ans[x] = arr[path[l]].depth;
        for (auto k: children[x]) {
            dfs(k);
        }
        path.pop_back();
    };
    dfs(1);
    for (int i = 2; i <= n;i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
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