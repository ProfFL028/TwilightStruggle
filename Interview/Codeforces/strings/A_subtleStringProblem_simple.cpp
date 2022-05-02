// codeforces: https://codeforces.com/contest/1673/problem/A

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    string s;
    cin >> s;
    int sz = s.size();
    if (sz == 1) {
        cout << "Bob " << (s[0] - 'a' + 1) << endl;
        return;
    }

    int ans = 0;
    for (int i = 0; i < sz; i++) {
        ans += s[i] - 'a' + 1;
    }
    if (sz & 1) {
        if (s[0] < s[sz - 1]) {
            ans -= 2 * (s[0] - 'a' + 1);
        } else {
            ans -= 2 * (s[sz - 1] - 'a' + 1);
        }
    }

    if (ans > 0) {
        cout << "Alice " << ans << endl;
    } else {
        cout << "Bob " << ans << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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