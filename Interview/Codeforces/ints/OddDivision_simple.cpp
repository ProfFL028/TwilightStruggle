// codeforces:  https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/F

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
    string arr;
    cin >> arr;
    if (arr[0] == '0') {
        cout << "-1" << endl;
        return;
    }
    int len = strlen(arr.c_str());
    ll ans = 0;
    bool odd = (arr[0] - '0') & 1;
    int i = 1;
    while (i < len) {
        int x = arr[i] - '0';
        if (odd) {
            if (x != 0) {
                ans++;
                odd = x & 1;
            } else {
                odd = false;
            }
        } else {
            odd = x & 1;
        }
        i++;
    }
    int x = arr[len - 1] - '0';
    if (x & 1) {
        ans++;
    }
    if (ans > 0) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
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