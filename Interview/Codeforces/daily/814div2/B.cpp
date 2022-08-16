// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n, k;
    cin >> n >> k;
    if (k % 4 == 0) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        if (k % 4 == 2) {
            for (int i = 1; i <= n/2; i++) {
                if (i % 2 == 0) {
                    cout << (i*2-1)  << " "  << i*2<< endl;
                } else {
                    cout << i*2 << " " << (i*2-1) << endl;
                }

            }
        } else {
            for (int i = 1; i <= n/2; i++) {
                cout << (i*2-1) << " " << i*2 << endl;
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