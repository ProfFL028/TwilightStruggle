// codeforces: https://codeforces.com/contest/1670/problem/C

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

int testCase = 1;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> arr1(n+1), arr2(n+1), arr3(n+1);
    vector<int> visited(n + 1, false);
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> arr2[i];
    }
    map<int, pair<int, int>> a, b;
    for (int i = 0; i < n; i++) {
        a[arr1[i]] = make_pair(arr2[i], i);
        b[arr2[i]] = make_pair(arr1[i], i);
    }
    for (int i = 0; i < n; i++) {
        cin >> arr3[i];
        if (arr3[i] > 0) {
            visited[arr3[i]] = true;
            if (arr1[i] == arr3[i]) {
                int cur = arr2[i];
                while (!visited[cur]) {
                    visited[cur] = true;
                    cur = arr2[a[cur].second];
                }
            } else {
                int cur = arr1[i];
                while (!visited[cur]) {
                    visited[cur] = true;
                    cur = arr1[b[cur].second];
                }
            }
        }
    }
    int groups = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && i != a[i].first) {
            groups++;
            visited[i] = true;
            int cur = a[i].first;
            while (!visited[cur]) {
                visited[cur] = true;
                cur = arr2[a[cur].second];
            }
        }
    }
    ll ans = 1;
    for (int i = 0; i < groups; i++) {
        ans = (ans * 2) % MOD;
    }
//    while (groups) {
//        if (groups & 1) {
//            ans = (ans * tmp) % MOD;
//        }
//        tmp = (tmp * tmp) % MOD;
//        groups >>= 1;
//    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
#endif
    fast()

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