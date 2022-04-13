// codeforces:  https://codeforces.com/contest/1661/problem/B

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;


void solve() {
    int x;
    cin >> x;

    if (x == 0) {
        cout << 0 << endl;
        return ;
    }
    int ans = 15;
    int count = 0;
    if (x & 1) {
        count++;
        x++;
    }
    for (int j = 0; j < 15; j++) {
        int k = __builtin_ctz(x); // zero count from right
        ans = min(ans, 15 - k + count);
        x += 2;
        count += 2;

        if (x > 32768)break;
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