// codeforces:  https://codeforces.com/contest/1665/problem/B

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
    int n;
    cin >> n;
    int x;
    map<int, int> numCounts;
    int m = 0;
    for (auto i = 0; i < n; i++) {
        cin >> x;
        if (numCounts.find(x) != numCounts.end()) {
            numCounts[x]++;
        } else {
            numCounts[x] = 1;
        }
        if (numCounts[x] > m) {
            m = numCounts[x];
        }
    }

    int ans = 0;
    while (m < n) {
        ans++; // copy
        if (m <= n / 2) {
            ans += m;
        } else {
            ans += (n - m);
        }
        m *= 2;
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