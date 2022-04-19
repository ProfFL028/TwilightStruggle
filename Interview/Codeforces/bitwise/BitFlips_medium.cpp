// codeforces:   https://codeforces.com/contest/1659/problem/B

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
    ll n, k;
    cin >> n >> k;
    string arr;
    cin >> arr;

    if (k & 1) {
        for (int i = 0; i < n; i++) {
            if (arr[i] == '0')
                arr[i] = '1';
            else
                arr[i] = '0';
        }
    }
    vector<ll> flipCounts(n, 0);
    /**
     * --k; arr[n-1]++; // move to back.
     */
    for (int i = 0; i < n; i++) {
        if (k == 0) break;
        if (arr[i] == '0' && (arr[i] & 1 ^ 1)) {
            flipCounts[i]++;
            --k;
            arr[i] = '1';
        }
    }
    if (k > 0) {
        flipCounts[n - 1] += k;
        if (k & 1)
            arr[n - 1] = '0';
    }
    cout << arr << endl;
    for (auto & v: flipCounts) {
        cout << v << " ";
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