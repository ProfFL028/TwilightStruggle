// codeforces: https://codeforces.com/contest/1673/problem/E
// tags: number theory; combinatorics; bitmasks;

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
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (auto &x: arr) {
        cin >> x;
    }

    vector<char> ans((1 << 20), '0');
    for (int l = 0; l < n; l++) {
        ll p = 1;
        for (int r = l; r < n; r++) {
            if (r == l) p *= arr[l];
            else {
                if (arr[r] >= 20)
                    break;
                else
                    p *= (1ll << arr[r]);
            }

            if (p >= (1 << 20)) break;
            int m = n - r + l - 3;
            int q = k - 2;
            if (l == 0) {
                m++;
                q++;
            }
            if (r == (n - 1)) {
                m++;
                q++;
            }
            if(m>=q && (m==0 || (q>0 && ((m-1)|(q-1))==(m-1))))
                ans[p] = '1' + '0' - ans[p];
        }
    }

    bool start = false;
    for (int i = (1 << 20) - 1; i >= 0; --i) {
        if (start) cout << ans[i];
        else {
            if (ans[i] == '1') {
                cout << ans[i];
                start = true;
            }
        }
    }
    if (!start) {
        cout << 0 << endl;
    }
    cout << endl;
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