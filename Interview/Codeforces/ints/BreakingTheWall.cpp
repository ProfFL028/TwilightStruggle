// codeforces: https://codeforces.com/contest/1674/problem/E?f0a28=1

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    int a1 = INT_MAX, a2 = INT_MAX; // min1, min2
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (a1 >= arr[i]) {
            a2 = a1;
            a1 = arr[i];
        } else if (a2 >= arr[i]) {
            a2 = arr[i];
        }
    }

    int ans = (a1 + 1) / 2 + (a2 + 1) / 2;

    for (int i = 0; i < n - 2; i++) {
        int a = arr[i];
        int b = arr[i + 2];
        int solution2 = min(a, b) + (max(a, b) - min(a, b) + 1) / 2;
        ans = min(ans, solution2);
    }

    for (int i = 0; i < n - 1; i++) {
        int a = arr[i];
        int b = arr[i + 1];
        if (a < b) swap(a, b);

        if (a >= 2 * b) {
            ans = min(ans, (a + 1) / 2);
            continue;
        }

        int diff = a - b;
        a -= 2 * diff;
        ans = min(ans, diff + a / 3 * 2 + a % 3);
    }

    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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