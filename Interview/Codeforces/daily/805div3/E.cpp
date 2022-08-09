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
    int n;
    cin >> n;
    vector<bool> a(n + 5, false), b(n + 5, false);
    bool isOK = true;
    while (n--) {
        int x, y;
        cin >> x >> y;

        if (isOK) {
            if (x == y) {
                isOK = false;
            } else {
                if (a[x] || a[y]) {
                    if (b[x] || b[y]) {
                        isOK = false;
                    } else {
                        b[x] = true;
                        b[y] = true;
                    }
                } else {
                    a[x] = true;
                    a[y] = true;
                }
            }
        }
    }
    if (isOK) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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