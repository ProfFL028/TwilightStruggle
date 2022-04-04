// codeforces:  https://codeforces.com/contest/1660/problem/E

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

    char matrix[2005][2005];
    int oneCount = 0;
    for (int i = 0; i < n; i++) {
        cin >> matrix[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            oneCount += matrix[i][j] == '1';
        }
    }
    int maxCount = 0;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < n; j++) {
            cur += matrix[(i + j) % n][j] - '0';
        }
        maxCount = max(maxCount, cur);
    }
    int ans = n - maxCount + (oneCount - maxCount);
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