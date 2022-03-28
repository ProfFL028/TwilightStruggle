// https://codeforces.com/contest/1658/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

int arr[1000005];

void solve() {
    int n;
    cin >> n;
    int oneCount = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        oneCount += arr[i] == 1;
    }

    if (oneCount != 1) {
        cout << "NO" << endl;
        return;
    }
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1] + 1) {
            cout << "NO" << endl;
            return;
        }
    }
    if (arr[0] > arr[n - 1] + 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
#endif
    fast()

    int testCase = 0;
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