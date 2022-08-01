// codeforces:

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

const int MM = 1e9+2;
void solve() {
    int n;
    cin >> n;
    vector<int> arr;
    vector<int> left(MM, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (i > x)  {
            arr.push_back(i);
            left[x]++;
        }
    }
    for (int i = MM-2; i>=0; i--) {
        left[i] += left[i+1];
    }

    ll ans = 0;
    for (auto x : arr) {

    }
    cout << ans << endl;
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