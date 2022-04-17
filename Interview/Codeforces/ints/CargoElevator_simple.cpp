// codeforces:  https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/D

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;


void solve() {
    int n;
    cin >> n;
    int x;
    int c100 = 0, c50 = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x == 100) {
            c100++;
        } else {
            c50++;
        }
    }
    int ans = 0;
    if (c50 >= c100) {
        ans = (c100 * 100 + c50 * 50 - 1) / 150 + 1;
    } else {
        ans = c100;
    }

    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
#endif
    fast()

    int testCase = 1;
    // cin >> testCase;
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