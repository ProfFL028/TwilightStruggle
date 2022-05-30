// codeforces: https://codeforces.com/contest/1686/problem/D

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

int sortByLength(pair<int, string> a, pair<int, string> b) {
    return a.first - b.first != 0 ? a.first - b.first : a.second[0] - b.second[0];
}

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    string s;
    cin >> s;

    vector<pair<int, string>> splits;
    int sz = a + b + (c << 1) + (d << 1);

    // Check if count of a in s satisfies.
    int aCount = 0;
    for (int i = 0; i < sz; ++i) {
        aCount += s[i] == 'A';
    }
    if (aCount != a + c + d) {
        cout << "NO" << endl;
    }

    int begin = 0;
    for (int i = 1; i < sz; i++) {
        if (s[i] == s[i - 1]) {
            string sub = s.substr(begin, i);
            splits.emplace_back(sub.size(), sub);
            begin = i;
        }
    }
    sort(splits.begin(), splits.end(), sortByLength);

    // Satisfy AB string even size and begin with A.
    for (auto &sub: splits) {
        if ((sub.first & 1) ^ 1) {
            int satisfy = sub.first / 2;
            if (sub.second[0] == 'A') {
                if (c > satisfy) {
                    c -= satisfy;
                    sub = make_pair(0, "");
                } else {
                    int remain = (satisfy - c) << 1;
                    sub = make_pair(remain, sub.second.substr(0, remain));
                    break;
                }
            }
        }
    }
    if (c > 0) {
        // get AB from ABABA... where substring's length is odd and substring begins with A.
        for (auto &sub: splits) {
            if (sub.first & 1 && sub.second[0] == 'A') {
                int satisfy = sub.first / 2;
                if (c > satisfy) {
                    c -= satisfy;

                }
            }
        }
    }
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