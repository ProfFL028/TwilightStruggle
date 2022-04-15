// codeforces: https://codeforces.com/contest/1661/problem/F

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int maxLen = 10e6 + 5;
ll arr[maxLen];

void solve() {
    ll n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll m;
    cin >> m;

    ll energy = 0;
    ll ans = 0;
    priority_queue<ll> queue;
    energy += arr[0] * arr[0];
    if (arr[0] > 1) {
        queue.push(arr[0]);
    }
    for (int i = n - 1; i >= 1; i--) {
        ll diff = arr[i] - arr[i-1];
        if (diff > 1) {
            queue.push(diff);
            energy += (diff * diff);
        } else {
            energy += 1;
        }
    }

    while (energy > m && !queue.empty()) {
        ll maxDistance = queue.top();
        queue.pop();
        energy -= (maxDistance * maxDistance);
        ll split = maxDistance / 2;
        energy += (split * split) + (maxDistance - split) * (maxDistance - split);
        if (split> 1) {
            queue.push(split);
        }
        if ((maxDistance - split) > 1) {
            queue.push(maxDistance - split);
        }
        ans++;
    }
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
    // cin >> testCase;
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