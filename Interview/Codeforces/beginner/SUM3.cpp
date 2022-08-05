// codeforces:  https://codeforces.com/contest/1692/problem/F

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
    int n;
    cin >> n;
    vector<int> arr(10, 0);
    vector<int> checkArr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr[x % 10]++;
        if (arr[x % 10] <= 2) {
            checkArr.push_back(x % 10);
        }
    }

    string ok = "NO";
    if (arr[1] >= 3) {
        ok = "YES";
    } else {
        for (int i = 0; i < checkArr.size(); i++) {
            for (int j = i + 1; j < checkArr.size(); j++) {
                for (int k = j + 1; k < checkArr.size(); k++) {
                    if ((checkArr[i] + checkArr[j] + checkArr[k]) % 10 == 3) {
                        ok = "YES";
                        cout << ok << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << ok << endl;
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