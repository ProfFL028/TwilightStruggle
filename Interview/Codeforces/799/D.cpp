// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    string s;
    int h, m, t;
    cin >> s >> t;
    h = stoi(s.substr(0, 2));
    m = stoi(s.substr(3, 2));
    int oh = h, om=m;

    int ht = t / 60;
    int mt = t % 60;
    int ans = 0;
    do {
        string sh = h >= 10 ? to_string(h) : "0" + to_string(h);
        string sm = m >= 10 ? to_string(m) : "0" + to_string(m);
        s = sh + sm;
        string rs = s;
        reverse(s.begin(), s.end());
        ans += (rs == s);
        h += ht;
        m += mt;
        if (m >= 60) {
            h++;
            m -= 60;
        }
        if (h >= 24) {
            h -= 24;
        }
    } while (oh !=h || om != m);

    cout << ans << endl;
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