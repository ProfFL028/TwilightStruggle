// codeforces:  https://codeforces.com/contest/1670/problem/A

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<ll> arr(n);
    int negCount = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] < 0) {
            negCount++;
        }
    }
    bool ans = true;
    for (int i = 0; i < n-1; i++) {
        if (i < negCount - 1) {
            ans = abs(arr[i]) >= abs(arr[i + 1]);
        } else if (i >= negCount) {
            ans = abs(arr[i]) <= abs(arr[i + 1]);
        }
        if (!ans)
            break;
    }
    if (ans)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

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