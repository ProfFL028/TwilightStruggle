// codeforces:

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 1e9 + 7;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int ans = 0;
    set<int> s;
    stack<int> stk;
    stk.push(arr[0]);
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (s.contains(arr[i])) {
            while (!stk.empty()) {
                s.insert(stk.top());
                stk.pop();
            }
            mx = 0;
        } else {
            if (arr[i] < mx) {
                while (!stk.empty()) {
                    s.insert(stk.top());
                    stk.pop();
                }
            }
            mx = arr[i];
            stk.push(arr[i]);
        }
    }

    cout << s.size() << endl;
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