// codeforces: https://codeforces.com/contest/1676/problem/C

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
    int n, s;
    cin >> n >> s;
    vector<vector<char>> arr(n, vector<char>(s, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < s; j++)
            cin >> arr[i][j];
    }

    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            int dis = 0;
            for (int k = 0; k < s; k++) {
                dis += (abs(arr[i][k] - arr[j][k]));
            }
            ans = min(ans, dis);
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