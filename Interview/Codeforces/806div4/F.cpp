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
<<<<<<< HEAD
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
=======
    vector<int> arr(n+1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    ll ans = 0;
    vector<int> goods;
    for (int i = 1; i <= n; i++){
        if (arr[i] < i) {
            ans += (ll)(lower_bound(goods.begin(), goods.end(), arr[i]) - goods.begin());
            goods.push_back(i);
        }
    }
>>>>>>> 44ae2715f24765c39dd70e7492ff73a597790ec0

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