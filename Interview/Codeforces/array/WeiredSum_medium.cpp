// codeforces: https://codeforces.com/contest/1648/problem/A

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n, m;
    cin >> n >> m;

    map<int, vector<tuple<int, int>>> points;
    int c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> c;
            if (points.find(c) == points.end()) {
                points[c] = vector<tuple<int, int>>();
            }
            points[c].emplace_back(i + 1, j + 1);
        }
    }

    ll ans = 0;
    for (auto point: points) {
        auto coords = point.second;
        vector<int> a, b;
        /**
         * quick solution for computer all manhantten distance in an array.
         * a1-a2+a1-a3+...+a1-an= n*a1 - (a1+a2+a3+...+an)
         * a2-a3+a2-a4+...+a2-an= (n-1)*a1 - (a2+a3+...+an)
         */
        ll x = 0, y = 0;
        for (auto p: coords) {
            a.push_back(get<0>(p));
            b.push_back(get<1>(p));
            x += get<0>(p);
            y += get<1>(p);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ll sz = a.size();
        for (auto i: a) {
            ans += x - sz * i;
            sz--;
            x -= i;
        }
        sz = b.size();
        for (auto i: b) {
            ans += y - sz * i;
            sz--;
            y -= i;
        }
        // simple but slow solution.
//        for (int i = 0; i < v.size() - 1; i++) {
//            for (int j = i + 1; j < v.size(); j++) {
//                ans += abs(get<0>(v[i]) - get<0>(v[j]));
//                ans += abs(get<1>(v[i]) - get<1>(v[j]));
//            }
//        }
    }
    cout << ans << endl;
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