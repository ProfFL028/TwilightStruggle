// codeforces: https://codeforces.com/contest/1686/problem/A

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
    ll s = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s += arr[i];
    }

    for (int i = 0; i < n; i++) {
        double x = (s - arr[i]) * 1.0 / (n - 1);
        if (x == arr[i]) {
            cout << "YES" << endl;
            return ;
        }
    }
    cout << "NO" << endl;
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