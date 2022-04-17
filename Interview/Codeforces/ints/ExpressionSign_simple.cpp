// codeforces:  https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/C
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
    ll a , b;
    cin >> a >> b;
    if (a == 0) {
        cout << 0 << endl;
        return ;
    }
    if (a > 0) {
        cout << 1 << endl;
        return ;
    }
    if (b & 1) {
        cout << -1 << endl;
    } else {
        cout << 1 << endl;
    }

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