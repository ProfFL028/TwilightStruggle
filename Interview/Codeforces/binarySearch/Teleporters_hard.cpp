// codeforces:  https://codeforces.com/contest/1661/problem/F

#include <bits/stdc++.h>

using namespace std;

#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

/**
 * Minimal energy would be used if we can build n stations in distances.
 * @param distance
 * @param stations
 * @return
 */
ll minEnergy(int distance, int stations) {
    if (stations < 0) {
        return LLONG_MAX;
    }
    stations++;
    if (stations >= distance)
        return distance;
    int splitCount = distance / stations;
    return 1ll * (stations - distance % stations) * splitCount * splitCount +
           1ll * (distance % stations) * (splitCount + 1) * (splitCount + 1);
}

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = n - 1; i >= 1; i--) {
        arr[i] -= arr[i - 1];
    }
    ll m;
    cin >> m;

    ll stations = 0, energy = 0;
    /**
     * At least how many stations need to build to satisfy maxEnergy.
     */
    function<void(long long)> noMoreThan = [&](ll maxEnergy) {
        stations = 0, energy = 0;
        for (auto &val: arr) {
            int left = 0, right = val;
            while (right - left > 1) {
                int mid = (left + right) >> 1;
                // core code.
                // same as max energy can be.
                if (minEnergy(val, mid - 1) - minEnergy(val, mid) > maxEnergy)
                    left = mid;
                else
                    right = mid;
            }
            stations += left;
            energy += minEnergy(val, left);
        }
    };

    /**
     * Binary search maxEnergy.
     */
    ll left = 0, right = 1e18;
    while (right - left > 1) {
        ll mid = (left + right) >> 1;
        noMoreThan(mid);
        if (energy > m)
            right = mid;
        else
            left = mid;
    }

    noMoreThan(right);
    ll ans = stations;
    ll diff = energy - m;
    /**
     * add extra stations that missing.
     */
    ans += (diff + right - 1) / right;
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

