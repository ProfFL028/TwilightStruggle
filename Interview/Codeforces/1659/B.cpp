// codeforces:  https://codeforces.com/contest/1659/problems

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
    vector<ll> ans(n, 0);
    string res = arr;
    ll flipCount = 0;
    if (k == 0) {
        cout << arr << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        return;
    }
    int count0 = 0;
    if (arr[0] == '1' && (k & 1)) {
        k--;
        ans[0]++;
        for (int i = 1; i < n; i++) {
            if (arr[i] == '1')
                arr[i] = '0';
            else
                arr[i] = '1';
        }
    }
    if (k == 0) {
        cout << arr << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        return;
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