// codeforces: 
// tag: tree
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
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    int x = a + c - b;
    if ((x & 1) || (x < 0)) {
        cout << "NO" << endl;
        return;
    }
    if (a + b - c < 0 || b + c - a < 0) {
        cout << "NO" << endl;
        return;
    }
    x >>= 1;
    if (1 + a + c - x > n) {
        cout << "NO" << endl;
        return ;
    }
    cout << "YES" << endl;
    if (a != b + c) {
        int pre = 1, next = 4;
        for (int i = 0; i < a - 1; i++) {
            cout << pre << " " << next << endl;
            pre = next++;
        }
        cout << pre << " 2" << endl;
        if (x == 0) {
            pre = 1;
        } else if (x == a) {
            pre = 2;
        } else {
            pre = 4 + (x - 1);
        }
        for (int i = x; i < c - 1; i++) {
            cout << pre << " " << next << endl;
            pre = next++;
        }
        cout << pre << " 3" << endl;
        pre = 3;
        for (int i = 1 + a + c - x; i < n; i++) {
            cout << pre << " " << next << endl;
            pre = next++;
        }
    } else {
        int pre = 2, next = 4;
        for (int i = 0; i < b - 1; i++) {
            cout << pre << " " << next << endl;
            pre = next++;
        }
        cout << pre << " 3" << endl;
        pre = 3;
        for (int i = 0; i < c - 1; i++) {
            cout << pre << " " << next << endl;
            pre = next++;
        }
        cout << pre << " 1" << endl;
        pre = 1;
        for (int i = 1 + b + c - 0; i < n; i++) {
            cout << pre << " " << next << endl;
            pre = next++;
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