// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> arr;
    arr.push_back(0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x == 1) {
            arr.push_back(i);
        }
    }

    int ans = INT_MAX;
    int sz = arr.size();
    for (int i = s; i < sz; i++) {
        int mv = arr[i - s];
        if (i != sz - 1) {
            mv += (n - arr[i + 1] +1);
        }
        ans = min(mv, ans);
    }
    if (ans == INT_MAX) {
        cout << "-1" << endl;
    } else {
        cout << ans << endl;
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