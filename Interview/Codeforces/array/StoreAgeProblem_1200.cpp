// codeforces: https://codeforces.com/contest/1679/problem/B

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
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1, 0);
    ll s = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        s += arr[i];
    }

    int all = -1;
    set<int> idx;
    while (q--) {
        int a, b, c;
        cin >> a;
        if (a == 1) {
            cin >> b >> c;
            if (all == -1 || idx.find(b) != idx.end()) {
                s = s + c - arr[b];
            } else {
                s = s + c - all;
            }
            idx.insert(b);
            arr[b] = c;
            cout << s << endl;
        } else if (a == 2) {
            cin >> b;
            s = 1ll * n * b;
            // arr.assign(n + 1, b);
            cout << s << endl;
            all = b;
            idx.clear();
        }
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