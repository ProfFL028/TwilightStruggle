// codeforces:  https://codeforces.com/contest/1673/problem/D

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

const ll MOD = 1e9 + 7;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

void solve() {
    ll bMin, bDiff, bSize, bMax;
    ll cMin, cDiff, cSize, cMax;
    cin >> bMin >> bDiff >> bSize;
    cin >> cMin >> cDiff >> cSize;

    bMax = bMin + (bSize - 1) * bDiff;
    cMax = cMin + (cSize - 1) * cDiff;

    if (cDiff % bDiff || cMax > bMax || cMin < bMin) {
        cout << "0" << endl;
    } else if ((bMin % bDiff + bDiff) % bDiff != (cMin % bDiff + bDiff) % bDiff) {
        cout << "0" << endl;
    } else if ((cMin - cDiff < bMin) || (cMax + cDiff > bMax)) {
        cout << "-1" << endl;
    } else {
        ll ans = 0;
        for (int i = 1; i <= sqrt(cDiff); i++) {
            if (cDiff % i) continue;
            if (lcm(i, bDiff) == cDiff) {
                ans += (cDiff / i) * (cDiff / i);
                ans %= MOD;
            }
            if (i != cDiff / i && lcm(cDiff / i, bDiff) == cDiff) {
                ans += i * i;
                ans %= MOD;
            }
        }
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