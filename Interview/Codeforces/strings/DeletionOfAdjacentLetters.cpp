#include <bits/stdc++.h>
using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    string str;
    cin >> str;
    char letter;
    cin >> letter;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == letter) {
            if (i % 2 == 0) {
                cout << "YES" << endl;
                return ;
            }
        }
    }
    cout << "NO" << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_dal.txt", "r", stdin);
    freopen("../data/output_dal.txt", "w", stdout);
    freopen("../data/error_dal.txt", "w", stderr);
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