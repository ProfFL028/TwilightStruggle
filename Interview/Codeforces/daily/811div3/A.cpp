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
    int n;
    cin >> n;
    int h, m;
    cin >> h >> m;
    int diff = INT_MAX;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int hDiff = a - h;
        if (hDiff < 0)
            hDiff += 24;
        int mDiff = b - m;
        if (mDiff < 0) {
            hDiff--;
            mDiff += 60;
            if (hDiff < 0)
                hDiff = 23;
        }
        diff = min(diff, hDiff * 60 + mDiff);
    }
    cout << diff / 60 << " " << diff % 60 << endl;

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