// codeforces: https://codeforces.com/contest/1662/problem/H

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void solve() {
    int a, b;
    cin >> a >> b;
    set<int> result;
    result.insert(1);
    result.insert(2);

    int g1 = gcd(a - 1, b - 1);
    int g2 = gcd(a - 2, b);
    int g3 = gcd(a, b - 2);
    result.insert(g1);
    result.insert(g2);
    result.insert(g3);

    for (int i = 2; i * i <= max(g1, max(g2, g3)); i++) {
        if ((g1 % i) == 0) {
            result.insert(i);
            result.insert((g1 / i));
        }
        if ((g2 % i) == 0) {
            result.insert(i);
            result.insert(g2 / i);
        }
        if ((g3 % i) == 0) {
            result.insert(i);
            result.insert(g3 / i);
        }
    }

    print(result);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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