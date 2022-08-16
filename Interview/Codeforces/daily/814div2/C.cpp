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
    vector<int> arr(n + 1), mx(n + 1, 0), tail(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        mx[i] = max(mx[i - 1], arr[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (arr[i] >= mx[i]) {
            for (int j = i + 1; j <= n; j++) {
                if (arr[j] > arr[i]) {
                    tail[i] = j;
                    break;
                }
            }
        }
    }

    while (q--) {
        ll ans = 0;
        ll a, b;
        cin >> a >> b;

        if (arr[a] >= mx[a] && b >= a - 1) {
            if (tail[a] == 0) {
                ans = b - a + 1;
            } else {
                ans = min(tail[a]-1ll, b) - a;
            }
            if (a > 1) {
                ans++;
            }
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