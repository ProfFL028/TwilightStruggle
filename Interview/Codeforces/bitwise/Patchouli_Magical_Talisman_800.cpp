// codeforces: https://codeforces.com/contest/1688/problem/B

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
    vector<int> arr(32, 0);
    int oddCount = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int k = 0;
        while ((x & 1) ^ 1) {
            k++;
            x >>= 1;
        }
        arr[k]++;
    }

    int ans = 0;
    int m = 0;
    for (int i = 1; i <= 31; i++) {
        ans += arr[i];
        if (arr[0] == 0 && m == 0 && arr[i] > 0) {
            m = arr[i];
            ans += (i - 1);
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