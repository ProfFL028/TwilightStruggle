// codeforces: https://codeforces.com/contest/1678/problem/C

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
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> bd(n, 0);
    for (int b = 1; b < n; b++) {
        for (int d = b + 1; d < n; d++) {
            if (arr[b] > arr[d]) bd[b]++;
        }
    }

    ll ans = 0;
    vector<int> s(n+1, 0);
    for (int c = 2; c < n; c++) {
        for (int a = 1; a < c; a++) {
            if (arr[a] > arr[c]) bd[a]--;
        }
        s[0] = 0;
        for (int b = 0; b < c; b++) {
            s[b+1] = s[b] + bd[b];
        }
        for (int a = 0; a < c; a++) {
            if (arr[a] < arr[c]) ans += s[c] - s[a+1];
        }
    }

    cout << ans << endl;
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