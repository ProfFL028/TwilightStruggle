// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/K

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    int ans = 0;
    vector<int> up(n + 1, 0);
    vector<int> down(n + 1, 0);

    bool upOrDown = false;
    for (int i = 1; i <= n; i++) {
        up[i] = 1;
        down[i] = 1;
        for (int j = 1; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (up[j] & 1) {
                    up[i] = max(up[i], up[j]+1);
                }
                if (down[j]&1^1) {
                    down[i] = max(down[i], down[j]+1);
                }
            } else if (arr[j] > arr[i]) {
                if (up[j] & 1^1) {
                    up[i] = max(up[i], up[j]+1);
                }
                if (down[j]&1) {
                    down[i] = max(down[i], down[j]+1);
                }
            }
        }
        if (ans < up[i]) {
            ans = up[i];
            upOrDown = true;
        }
        if (ans < down[i]) {
            ans = down[i];
            upOrDown = false;
        }
    }

    cout << (n-ans) << endl;
    if (upOrDown) {
        for (int i = 2; i <= n; i++) {
            if (up[i] == up[i-1]) {
                cout << (i-1) << " ";
            }
        }
        cout << endl;
    } else {
        for (int i = 2; i <= n; i++) {
            if (down[i] == down[i-1]) {
                cout << (i-1) << " ";
            }
        }
        cout << endl;
    }
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