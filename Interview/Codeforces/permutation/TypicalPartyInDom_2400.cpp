// codeforces: https://codeforces.com/contest/1679/problem/E

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 998244353;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;


void solve() {
    int n;
    cin >> n;
    vector<char> arr(n);
    int mark = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] == '?')
            mark++;
    }

    int q = 0;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        int sz = s.length();
        vector<char> m(26, 0);
        for (int i = 0; i < sz; i++) {
            m[s[i] - 'a'] = 1;
        }
        vector<int> powers(n * 2);
        powers[0] = 1;
        for (int i = 1; i < (2 * n); i++) {
            powers[i] = 1ll * powers[i - 1] * sz % MOD;
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            int pow = 0;
            int outsideMark = mark;
            if (arr[i] == '?') {
                int p = (++pow) + (--outsideMark);
                ans = (ans + powers[p]) % MOD;
            } else {
                ans = (ans + powers[mark]) % MOD;
            }
            int diff = 1;
            while ((i - diff) >= 0 && (i + diff) < n) {
                if (arr[i - diff] == '?' && arr[i + diff] == '?') {
                    outsideMark -= 2;
                    int p = (++pow) + (outsideMark);
                    ans = (ans + powers[p]) % MOD;
                } else {
                    if ((arr[i - diff] == '?' && m[arr[i + diff] - 'a']) ||
                        (arr[i + diff] == '?' && m[arr[i - diff] - 'a'])) {
                        int p = (pow) + (--outsideMark);
                        ans = (ans + powers[p]) % MOD;
                    } else if (arr[i - diff] == arr[i + diff]) {
                        ans = (ans + powers[pow + outsideMark]) % MOD;
                    } else {
                        break;
                    }
                }
                diff++;
            }
            diff = 0;
            pow = 0;
            outsideMark = mark;
            while ((i - diff) >= 0 && (i + diff + 1) < n) {
                if (arr[i - diff] == '?' && arr[i + diff + 1] == '?') {
                    outsideMark -= 2;
                    int p = (++pow) + (outsideMark);
                    ans = (ans + powers[p]) % MOD;
                } else {
                    if ((arr[i - diff] == '?' && m[arr[i + diff + 1] - 'a']) ||
                        (arr[i + diff + 1] == '?' && m[arr[i - diff] - 'a'])) {
                        int p = (pow) + (--outsideMark);
                        ans = (ans + powers[p]) % MOD;
                    } else if (arr[i - diff] == arr[i + diff + 1]) {
                        int p = (pow) + (outsideMark);
                        ans = (ans + powers[p]) % MOD;
                    } else {
                        break;
                    }
                }
                diff++;
            }
        }

        cout << ans << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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