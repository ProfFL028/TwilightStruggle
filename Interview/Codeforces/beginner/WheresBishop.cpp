// codeforces: https://codeforces.com/contest/1692/problem/C

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
    int k = 8;
    bool found = false;
    int x, y;
    for (int i = 1; i <= k; i++) {
        int c = 0;
        int p[2];
        for (int j = 1; j <= k; j++) {
            char x;
            cin >> x;
            if (x == '#') {
                p[c++] = j;
            }
        }
        if (!found && c >= 2) {
            found=true;
            y = (p[0] + p[1])/2;
            x = i + (y - p[0]);
        }
    }

    cout << x <<" " << y << endl;
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