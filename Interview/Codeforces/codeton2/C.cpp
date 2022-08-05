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
    int n, m;
    cin >> n >> m;
    vector<int> infected(m + 1), segment(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> infected[i];
    }
    sort(infected.begin() + 1, infected.end());
    for (int i = 2; i <= m; i++) {
        segment[i] = infected[i] - infected[i - 1] - 1;
    }
    segment[1] = n + infected[1] - infected[m] - 1;
    sort(segment.begin(), segment.end(), greater<>());
    int ans = m;
    for (int i = 0; i < m; i++) {
        int remains = segment[i] - i * 4;
        if (remains > 0) {
            ans += i * 4;
            ans += (remains == 1) ? 0 : 1;
        } else {
            ans += segment[i];
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