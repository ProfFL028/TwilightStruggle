// https://codeforces.com/contest/1658/problem/A

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
    int arrSize = 0;
    cin >> arrSize;
    char arr[100000];
    int ans = 0;
    cin >> arr;
    if (arr[1] == '0' && arr[0] == '0') {
        ans += 2;
    }
    for (int i = 2; i < arrSize; i++) {
        if (arr[i] == '0') {
            if (arr[i - 1] == '0') {
                ans += 2;
            } else {
                if (arr[i - 2] == '0') {
                    ans += 1;
                }
            }
        }
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