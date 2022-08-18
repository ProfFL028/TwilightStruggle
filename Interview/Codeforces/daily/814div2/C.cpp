// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1), win(n + 1, 0), lose(n + 1, 0);
    int mx = 0, lst = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i] > mx) {
            win[i] = i - 1;
            lose[lst] = i - 1;
            lst = i;
            mx = arr[i];
        }
    }
    if (arr[1] > arr[2]) {
        win[1] = 1;
    }
    while (q--) {
        int ans = 0;
        int a, b;
        cin >> a >> b;
        if (arr[a] == mx) {
            lose[a] = b+1;
        }
        if (win[a] > 0 && win[a] <= b) {
            ans = min(b+1, lose[a]) - win[a];
        }
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