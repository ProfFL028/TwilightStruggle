// codeforces:

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

struct cmp {
    constexpr bool operator()(pair<ll, ll> const &a, pair<ll, ll> const &b) const noexcept {
        return a.first >= b.first;
    }
};
typedef pair<ll, ll> pd;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    ll ans = 0;
    ll sum = 0;
    vector<ll> idx;
    priority_queue<pd, vector<pd>, cmp> q;
    for (int i = 0; i < n / 2; i++) {
        q.push(make_pair(arr[2 * i], 2 * i + 1));
        q.push(make_pair(arr[2 * i + 1], 2 * i + 2));

        auto t = q.top();
        q.pop();
        if (sum + t.first <= k) {
            sum += t.first;
            idx.push_back(t.second);
            ans++;
        } else {
            break;
        }
    }
    if (sum < k) {
        if (n & 1) {
            q.emplace(arr[n - 1], n);
        }
        while (!q.empty()) {
            auto t = q.top();
            q.pop();
            if (sum + t.first <= k) {
                sum += t.first;
                idx.push_back(t.second);
                ans++;
            } else {
                break;
            }
        }
    }

    cout << ans << endl;
    for (auto &e: idx) {
        cout << e << " ";
    }
    cout << endl;
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