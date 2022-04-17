// codeforces:  https://codeforces.com/contest/1659/problem/A

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
    int n, r, b;
    cin >> n >> r >> b;
    int k = r / (b + 1);
    int e = r % (b + 1);
    int nextB = k;
    int usedE = 0;
    int bc = 0;
    for (int i = 1; i <= r; i++) {
        cout << "R";
        if (i == nextB && bc < b) {
            cout << "B";
            nextB += k;
            bc++;
            if (usedE < e) {
                usedE++;
                nextB++;
            }
        }
    }
    cout << endl;
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