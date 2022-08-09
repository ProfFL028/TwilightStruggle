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
    vector<int> x, y;
    int a, b;
    for (int i = 0; i < n; i++) {
        cin >> a >>b;
        x.push_back(a);
        y.push_back(b);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    int minx = 0, miny=0, maxx=0, maxy=0;
    minx = min(x[0], minx);
    miny = min(y[0], miny);
    maxx = max(x[n-1], maxx);
    maxy = max(y[n-1], maxy);

    int ans = maxx + maxy - minx - miny;
    ans *= 2;
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