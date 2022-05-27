// codeforces: https://codeforces.com/contest/1681/problem/C

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
    vector<int> a(n + 1, 0), b(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<pair<int, int>> swaps;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] > a[j]) {
                swaps.emplace_back(i, j);
                swap(a[i], a[j]);
                swap(b[i], b[j]);
            }
        }
    }
    int fromIdx = 1;
    int endIdx = 1;
    bool inEqual = false;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i + 1]) {
            for (int j = fromIdx; j <= endIdx; j++) {
                for (int k = j + 1; k <= endIdx; k++) {
                    if (b[k] < b[j]) {
                        swaps.emplace_back(j, k);
                        swap(b[k], b[j]);
                    }
                }
            }

            if (b[i] > b[i + 1] || (fromIdx > 1 && b[fromIdx] < b[fromIdx - 1])) {
                ans = -1;
                break;
            }
            inEqual = false;
        } else { // a[i] == a[i+1]
            if (!inEqual) {
                inEqual = true;
                fromIdx = i;
            }
            endIdx = i + 1;
        }
    }
    if (inEqual) {
        for (int j = fromIdx; j <= endIdx; j++) {
            for (int k = j + 1; k <= endIdx; k++) {
                if (b[k] < b[j]) {
                    swaps.emplace_back(j, k);
                    swap(b[k], b[j]);
                }
            }
        }

        if (fromIdx > 1 && b[fromIdx] < b[fromIdx - 1]) {
            ans = -1;
        }
    }
    if (ans != -1) {
        cout << swaps.size() << endl;
        for (auto x: swaps) {
            cout << x.first << " " << x.second << endl;
        }
    } else {
        cout << ans << endl;
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