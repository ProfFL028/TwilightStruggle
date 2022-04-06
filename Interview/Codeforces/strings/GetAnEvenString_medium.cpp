// codeforces: 

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int LEN = 2 * 10e6 + 2;
char arr[LEN];

void solve() {
    vector<char> notFound;
    cin >> arr;
    int ans = 0;
    int i = 0;
    while (arr[i] != '\0') {
        bool found = false;
        for (auto v : notFound) {
            if (arr[i] == v) {
                found = true;
                break;
            }
        }
        if (found) {
            notFound.clear();
            ans--;
        } else {
            notFound.push_back(arr[i]);
            ans++;
        }
        i++;
    }

    cout << ans << endl;
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