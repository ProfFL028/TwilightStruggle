// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/I

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
    queue<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push(x);
    }
    queue<int> b;
    for (int i = 0; i < n; i++) {
        int y;
        cin >> y;
        b.push(y);
    }

    int ans = 0;
    while (ans<1000000 && !a.empty() && !b.empty()) {
        int topa = a.front(); a.pop();
        int topb = b.front(); b.pop();
        if (topa > topb) {
            a.push(topa);
            a.push(topb);
        } else {
            b.push(topb);
            b.push(topa);
        }
        ans++;
    }

    if (ans <1000000) {
        cout << ans << endl;
    } else {
        cout << "-1" << endl;
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