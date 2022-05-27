// codeforces: https://codeforces.com/contest/1681/problem/A

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 1e9 + 7;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &x: arr) {
        cin >> x;
    }
    cin >> n;
    vector<int> arr2(n);
    for (auto &x: arr2) {
        cin >> x;
    }
    int a = *max_element(arr.begin(), arr.end());
    int b = *max_element(arr2.begin(), arr2.end());
    if (a > b) {
        cout << "Alice" << endl;
        cout << "Alice" << endl;
    } else if (a < b) {
        cout << "Bob" << endl;
        cout << "Bob" << endl;
    } else {
        cout << "Alice" << endl;
        cout << "Bob" << endl;
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