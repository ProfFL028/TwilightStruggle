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
    map<int, int> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while ((x % 2) ^ 1) {
            x >>= 1;
        }
        m[x]++;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while ((x % 2) ^ 1) {
            x >>= 1;
        }
        while (x) {
            if (m.contains(x) && m[x] > 0) {
                m[x]--;
                break;
            } else {
                x >>= 1;
            }
        }
    }
    bool isOK = true;
    for (auto i : m) {
        if (i.second > 0) {
            isOK = false;
            break;
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