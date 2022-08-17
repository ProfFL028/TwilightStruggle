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

ll fibonacci[60];
map<ll, int> sumFib;
void init() {
    fibonacci[0] = 1;
    fibonacci[1] = 1;
    sumFib[1] = 0;
    ll sum = 2;
    sumFib[2] = 1;
    for (int i = 2; i < 60; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        sum += fibonacci[i];
        sumFib[sum] = i;
    }
}

void solve() {
    int n; cin >> n;
    ll sm = 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        sm += x;
        a[i] = x;
    }
    int lef = 0;
    long long tmp = 0;
    while (tmp < sm) {
        tmp += fibonacci[lef];
        lef++;
    }
    if (tmp != sm) {
        cout << "NO\n";
        return;
    }
    int pred = -1;
    for (int i = lef - 1; i >= 0; --i) {
        int imx = -1;
        int mx = *max_element(a.begin(), a.end());
        for (int j = 0; j < n; ++j) {
            if (j == pred) continue;
            if (a[j] == mx) {
                imx = j;
                break;
            }
        }
        if (imx == -1 || a[imx] < fibonacci[i]) {
            cout << "NO\n";
            return;
        }
        pred = imx;
        a[imx] -= fibonacci[i];
    }
    cout << "YES\n";
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
#endif
    fast()

    init();

    int testCase = 1;
    cin >> testCase;
    while (testCase--) {
        solve();
    }

#ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed : " << 1000 * (lld) clock() / (lld) CLOCKS_PER_SEC
         << " ms\n";
#endif
    return 0;
}