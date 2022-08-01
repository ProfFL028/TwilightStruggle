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
    int n, x;
    cin >> n >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (x >= 5e8) {
        cout << 0 << endl;
        return ;
    }

    int ans = 0;
    int mina = arr[0];
    int maxa = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxa) {
            if (arr[i]-mina > 2*x) {
                ans++;
                mina = maxa = arr[i];
            } else {
                maxa = arr[i];
            }
        } else if (arr[i] < mina) {
            if (maxa - arr[i] > 2 * x) {
                ans++;
                mina = maxa = arr[i];
            } else {
                mina = arr[i];
            }
        }
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