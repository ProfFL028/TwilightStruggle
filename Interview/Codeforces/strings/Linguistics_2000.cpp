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
        return;
    }

    int begin = 0;
    for (int i = 1; i < sz; i++) {
        if (s[i] == s[i - 1]) {
            string sub = s.substr(begin, i - begin);
            if (sub.size() > 1)
                splits.emplace_back(sub.size(), sub);
            begin = i;
        }
    }
    splits.emplace_back(sz - begin, s.substr(begin, sz));
    sort(splits.begin(), splits.end());

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
                    c = 0;
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
                    sub = make_pair(1, "A");
                } else {
                    int start = c * 2;
                    c = 0;
                    sub = make_pair(sub.first - start, sub.second.substr(start));
                    break;
                }
            }
        }
    }

    if (c > 0) {
        // get AB from BABAB... where substring's length is odd and substring begins with A.
        for (auto &sub: splits) {
            if (sub.first & 1 && sub.second[0] == 'B' && sub.first >= 3) {
                int satisfy = sub.first / 2;
                if (c > satisfy) {
                    c -= satisfy;
                    sub = make_pair(1, "B");
                } else {
                    int remain = sub.first - c * 2;
                    c = 0;
                    sub = make_pair(remain, sub.second.substr(0, remain));
                    break;
                }
            }
        }
    }

    if (c > 0) {
        for (int i = splits.size() - 1; i >=0; --i) {
            auto& sub = splits[i];
            if ((sub.first & 1) ^ 1 && sub.second[0] == 'B' && sub.first > 2) {
                int satisfy = sub.first / 2 - 1;
                if (c > satisfy) {
                    c -= satisfy;
                    sub = make_pair(0, "");
                } else {
                    int remain = sub.first - 2 * c - 2;
                    c = 0;
                    sub = make_pair(remain, sub.second.substr(0, remain));
                    break;
                }
            }
        }
    }
    if (c > 0) {
        cout << "NO" << endl;
    } else {
        for (auto sub: splits) {
            int satisfy = sub.first;
            if (sub.second[0] == 'A') {
                satisfy -= 1;
            }
            satisfy >>= 1;
            d -= satisfy;
            if (d <= 0) {
                break;
            }
        }
        if (d > 0) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
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