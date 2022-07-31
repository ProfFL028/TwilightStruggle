// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n+1, 0), infected(m);
    for (int i = 0; i < m; i++) {
        cin >> infected[i];
        arr[infected[i]] = 1;
    }
    set<pair<int, int>> lines;
    int maxLine = -1;
    int maxLineIndex = -1;
    for (int i = 0; i < m; i++) {
        lines.insert(make_pair(infected[i], infected[(i+1) % m]));
        if( i != m -1) {
            if (infected[i] - infected[i + 1] > maxLine) {
                maxLine = infected[i] - infected[i + 1];
                maxLineIndex = i;
            }
        } else {
            if (n - infected[i] + infected[0] > maxLine) {
                maxLine = n - infected[i] + infected[0];
                maxLineIndex = i;
            }
        }
    }
    arr[infected[maxLineIndex] - 1] = 1;
    int ans = 0;

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