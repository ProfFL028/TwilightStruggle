// https://codeforces.com/contest/1647/problem/D

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
bool check (int n)
{
    for(int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
void solve() {
    int x, d, cnt = 0;
    cin >> x >> d;
    while (x % d == 0)
        x /= d, ++cnt;
    if (cnt < 2)
        cout << "NO\n";
    else if (!check(x))
        cout << "YES\n";
    else if (check(d))
        cout << "NO\n";
    else if (cnt > (x * x == d) + 2)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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