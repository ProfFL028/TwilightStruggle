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

const int MAX_N = 200010;
int n, arr[MAX_N];
vector<int> c(MAX_N, 0);

void add(int x) {
    for (; x <= n; x += x & -x)
        c[x]++;
}

int query(int x) {
    int s = 0;
    for (; x; x -= x & -x)
        s += c[x];
    return s;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        arr[x] = i;
    }
    ll ans = 0;
    fill(c.begin(), c.end(), 0);

    for (int i = 1; i < n; i++) {
        int v = query(arr[i + 1]) - query(arr[i]);
        if (arr[i] > arr[i + 1])
            v += i - 1;
        ans += 1ll * v * (n - i), add(arr[i]);
    }

    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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