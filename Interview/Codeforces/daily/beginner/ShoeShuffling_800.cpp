// codeforces: https://codeforces.com/contest/1691/problem/B

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n == 1) {
        cout << "-1" << endl;
        return;
    }
    bool ok = arr[0] == arr[1] && arr[n - 1] == arr[n - 2];
    if (ok) {
        for (int i = 0; i < n; i++) {
            if (arr[i - 1] < arr[i] && arr[i] < arr[i + 1]) {
                ok = false;
                break;
            }
        }
    }
    if (ok) {
        int begin = 0;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] == arr[i + 1]) {
                cout << (i + 2) << " ";
            } else {
                cout << (begin + 1) << " ";
                begin = i + 1;
            }
        }
        cout << begin + 1 << " " << endl;
    } else {
        cout << "-1" << endl;
    }
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