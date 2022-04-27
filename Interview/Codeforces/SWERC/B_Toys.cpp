// codeforces: https://codeforces.com/contest/1662/problem/B

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    string bear, owl, raccoon;
    cin >> bear >> owl >> raccoon ;

    vector<string> result;
    for (int i = 0; i < bear.size(); i++) {
        result.push_back("0" + bear[i]);
    }
    for (int i = 0; i < owl.size(); i++) {
        bool putted = false;
        for (int j = 0; j < result.size(); j++) {
            if (result[j][0] == '0') {
                if (result[j][1] == owl[i]) {
                    result[j][0] = '1';
                } else {
                    result[j][0]= '2';
                    result[j] = result[j] + owl[i];
                }
                putted = true;
            }
        }
        if (!putted) {
            result.push_back("0" + owl[i]);
        }
    }
    for (int i = 0; i < raccoon.size(); i++) {
        bool putted = false;
        for (int j = 0; j < result.size(); j++) {
            if (result[j][0] == '0') {
                if (result[j][1] == raccoon[i]) {

                }
            }
        }
    }

    int ans = 0;

    cout << ans << endl;
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