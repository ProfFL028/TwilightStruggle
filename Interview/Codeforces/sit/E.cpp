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

void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    map<int, map<int, map<int, int>>> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            char x = arr[i][j];
            m[x][i][j] = 1;
        }
    }
    int ans = 0;
    for (auto &kv: m) {
        auto v = kv.second;
        auto e1 = v.begin();
        while (e1 != v.end()) {
            auto e2 = e1;
            e2++;
            while (e2 != v.end()) {
                int c = 0;
                for (auto l: e1->second) {
                    if (l.second == 1) {
                        if (e2->second[l.first] == 1) {
                            c++;
                        }
                    }
                }
                if (c >= 2) {
                    ans += (c * (c - 1)) / 2;
                }
                e2++;
            }
            e1++;
        }
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