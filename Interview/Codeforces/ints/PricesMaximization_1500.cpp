// codeforces: https://codeforces.com/contest/1690/problem/E

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
    int n, k;
    cin >> n >> k;
    vector<int> arr;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ans += x / k;
        if (x % k > 0) {
            arr.push_back(x % k);
        }
    }
    sort(arr.begin(), arr.end());
    int sz = arr.size();
    for(int i = 0, j = sz - 1; i < j; i++, j--){
        while(arr[i] + arr[j] < k && i < j) i++;
        if(i == j) break;
        ans++;
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