// codeforces: https://codeforces.com/contest/1673/problem/B

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
    map<char, int> m;
    int l = 0;
    bool repeat = false;
    for (int i = 0; i < sz; i++) {
        m[s[i]]++;
        if (!repeat) {
            if (m[s[i]] > 1) {
                repeat = true;
                if (s[i] == s[0]) {
                    l = i - 0;
                } else {
                    cout << "NO" << endl;
                    return ;
                }
            }
        } else {
            if (s[i] != s[i - l]) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
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