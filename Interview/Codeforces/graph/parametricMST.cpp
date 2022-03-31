// codeforces: https://codeforces.com/contest/1656/problem/F

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n;
    cin >> n;
    ll arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    ll sum = accumulate(arr + 1, arr + n, 0ll);
    ll k = sum + arr[0] * (n - 1);
    if (k > 0) {
        puts("INF");
        return;
    }

    sum *= arr[0];
    ll zx = sum - arr[0] * k;
    for (int i = 0; i < n - 1;) {
        ll l = arr[i], r = arr[i + 1];
        zx = max({zx, sum - l * k, sum - r * k});
        i++;
        if (i == n - 1)break;
        sum += (ll) arr[i] * (arr[n - 1] - arr[0]);
        k += arr[n - 1] - arr[0];
    }
    if (k < 0) {
        puts("INF");
        return;
    }
    printf("%lld\n", zx);
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