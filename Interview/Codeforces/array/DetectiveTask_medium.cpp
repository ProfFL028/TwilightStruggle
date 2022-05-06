// codeforces: https://codeforces.com/contest/1675/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    string s;
    cin >> s;
    int sz = s.length();

    int ans = 0;
    if (s[0] == '0' || s[sz - 1] == '1') {
        cout << "1" << endl;
        return;
    }
    size_t zeroPos = s.find('0');
    if (zeroPos != string::npos) {
        // contains 0
        for (int i =zeroPos-1; i >=0; i--) {
            ans++;
            if (s[i] == '1') {
                break;
            }
        }
        ans++;
        for (int i = zeroPos+1; i < sz; i++) {
            if (s[i] == '0') {
                break;
            } else if (s[i]=='1') {
                ans = 1;
                break;
            } else {
                s[i]++;
            }
        }
    }  else {
        // do not contains 0
        for (int i = sz-1; i>=0;i--) {
            if (s[i] == '?') ans++;
            else {
                ans++;
                break;
            }
        }
    }

    cout << ans << endl;
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