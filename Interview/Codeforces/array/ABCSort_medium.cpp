// codeforces: https://codeforces.com/contest/1674/problem/D

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
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n <= 2) {
        cout << "YES" << endl;
    } else {
        int cur1 = arr[n - 1], cur2 = arr[n - 2];
        int i = n - 3;
        bool isNotOk = false;
        while (i >= 0) {
            if (cur1 < arr[i] || cur2 < arr[i]) {
                isNotOk = true;
                break;
            }
            i--;
            if (i >= 0) {
                if (cur1 < arr[i] || cur2 < arr[i]) {
                    isNotOk = true;
                    break;
                }
                cur1 = arr[i + 1];
                cur2 = arr[i];
            }
            i--;
        }
        if (isNotOk) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }

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