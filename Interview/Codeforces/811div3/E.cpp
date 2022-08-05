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
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end(), greater<>());
    int dest = arr[0];
    if ((dest % 10) == 1) {
        dest += 1;
    } else if ((dest % 10) == 3) {
        dest += 9;
    } else if ((dest % 10) == 5) {
        dest += 5;
    } else if ((dest % 10) == 4) {
        dest += 18;
    } else if ((dest % 10) == 6) {
        dest += 6;
    } else if ((dest % 10) == 7) {
        dest += 25;
    } else if ((dest % 10) == 8) {
        dest += 14;
    } else if ((dest % 10) == 9) {
        dest += 23;
    }

    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[i-1]) {
            int cur = arr[i];
            if ((cur % 10) == 1) {
                cur += 1;
            } else if ((cur % 10) == 3) {
                cur += 9;
            } else if ((cur % 10) == 5) {
                cur += 5;
            } else if ((cur % 10) == 4) {
                cur += 18;
            } else if ((cur % 10) == 6) {
                cur += 6;
            } else if ((cur % 10) == 7) {
                cur += 25;
            } else if ((cur % 10) == 8) {
                cur += 14;
            } else if ((cur % 10) == 9) {
                cur += 23;
            }
            if (cur % 10 == 2) {
                if ((dest - cur) % 20 != 0) {
                    cout << "NO" << endl;
                    return ;
                }
            } else {
                if (dest != cur) {
                    cout << "NO" << endl;
                    return ;
                }
            }
        }
    }

    cout << "YES" << endl;
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