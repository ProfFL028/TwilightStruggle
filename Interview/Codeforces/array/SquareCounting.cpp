#include<iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    ll n, s;
    cin >> n >> s;

    cout << s / (n * n) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_SquareCounting.txt", "r", stdin);
    freopen("../data/output_SquareCounting.txt", "w", stdout);
    freopen("../data/error_SquareCounting.txt", "w", stderr);
#endif
    fast()

    int testCase = 0;
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