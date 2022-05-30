// codeforces: https://codeforces.com/contest/1686/problem/C
// zigzag
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
    vector<ll> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    // if array size is odd, it is impossible to be zigzag arranged.
    if (n & 1) {
        cout << "NO" << endl;
        return;
    }
    sort(arr.begin(), arr.end());
    int k = n >> 1;
    bool isOK = true;
    for (int i = 1; i < k; i++) {
        if (arr[i] >= arr[i+k-1]) {
            isOK = false;
            break ;
        }
    }

    if (isOK) {
        cout << "YES" << endl;
        for (int i = 0; i < k; i++) {
            cout << arr[i] << " " << arr[i + k] << " ";
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
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