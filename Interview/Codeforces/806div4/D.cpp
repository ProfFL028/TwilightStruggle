// codeforces:

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 1e9 + 7;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<string> arr(n);
    set<ll> hashcode;
    for (auto & s : arr) {
        cin >> s;
        ll code = 0;
        for (auto c : s)  {
            code = code * 26 +  (c - 'a' + 1);
        }
        hashcode.insert(code);
    }
    for (auto & s : arr) {
        int len = s.length();
        bool isConn = false;
        for (int i = 1; i < len; i++) {
            ll code = 0;
            for (int j = 0; j < i; j++) {
                code = code * 26 +  (s[j] - 'a' + 1);
            }
            if (hashcode.contains(code)) {
                code = 0;
                for (int j = i; j < len; j++) {
                    code = code * 26 +  (s[j] - 'a' + 1);
                }
                if (hashcode.contains(code)) {
                    isConn = true;
                    break;
                }
            }
        }
        if (isConn) {
            cout << "1";
        } else {
            cout << "0";
        }
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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