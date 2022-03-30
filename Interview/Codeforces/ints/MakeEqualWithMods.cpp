// codeforces: https://codeforces.com/contest/1656/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int maxLen = 10e6 + 5;
ll arr[maxLen];

void solve() {
    int n;
    cin >> n;
    int oneCount = 0;
    int zeroCount = 0;
    set<ll> numbers;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        oneCount += arr[i] == 1;
        zeroCount += (arr[i] == 0 || arr[i] == 2);
    }
    // if all numbers are 1, or no 1 in the array. it is ok.
    bool isOk = oneCount == 0 || (oneCount == n);
    if (isOk) {
        cout << "YES" << endl;
        return;
    }
    // if the array contains one, then it should not contain 0 or 2.
    if (zeroCount > 0) {
        cout << "NO" << endl;
        return;
    }
    // if the array contains one, then there check if arr[i]+1 is in the array.
    isOk = true;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 2) {
            if (numbers.find(arr[i] + 1) != numbers.end()) {
                isOk = false;
                break;
            } else {
                if (numbers.find(arr[i] - 1) != numbers.end()) {
                    isOk = false;
                    break;
                }
                numbers.insert(arr[i]);
            }
        }
    }
    if (isOk) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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