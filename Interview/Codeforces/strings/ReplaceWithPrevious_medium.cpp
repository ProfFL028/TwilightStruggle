// codeforces: https://codeforces.com/contest/1675/problem/E

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

void solve() {
    ll n, k;
    cin >> n >> k;
    char str[n];
    char minChar = 'z';
    char maxChar = 'a';
    int tmp = 0;
    char toA = 'a';
    for (int i = 0; i < n; i++) {
        cin >> str[i];
        if (tmp < k && str[i] > toA) {
            if (str[i] - 'a' <= k) {
                tmp = str[i] - 'a';
                toA = str[i];
            } else {
                maxChar = str[i];
                minChar = str[i] - k + tmp;
                tmp = k;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (str[i] <= toA) {
            cout << 'a';
        } else if (str[i] >= minChar && str[i] <= maxChar) {
            cout << minChar;
        } else {
            cout << str[i];
        }
    }
    cout << endl;
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