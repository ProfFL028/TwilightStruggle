// codeforces: https://codeforces.com/contest/1662/problem/A

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(11, 0);
    for (int i = 0; i < n; i++) {
        int x,y ;
        cin >> x >> y;
        arr[y] = max(x, arr[y]);
    }

    int ans = 0;
    for (int i = 1; i <= 10; i++) {
        if (arr[i] > 0) {
            ans+= arr[i];
        } else {
            ans = -1;
            break;
        }
    }
    if (ans > 0)
        cout << ans << endl;
    else
        cout << "MOREPROBLEMS" << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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