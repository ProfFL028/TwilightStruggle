// codeforces: https://codeforces.com/contest/1661/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

int n;
ll arr[300006];

ll find(ll targetHeight) {
    ll sum = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        ll diff = targetHeight - arr[i];
        sum += diff;
        cnt += (diff & 1);
    }

    return max(sum / 3 * 2 + sum % 3, 2 * cnt - 1);
}

void solve() {
    cin >> n;
    ll maxHeight = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        maxHeight = max(maxHeight, arr[i]);
    }
    ll ans = min(find(maxHeight), find(maxHeight + 1));
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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