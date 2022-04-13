// codeforces: https://codeforces.com/contest/1648/problem/B

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;


void solve() {
    ll n, c;
    cin >> n >> c;
    vector<int> arr(c + 1, 0);
    set<int> values;
    int x = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        arr[x] = 1;
        values.insert(x);
    }
    if (arr[1] == 0) {
        cout << "NO" << endl;
        return ;
    }
    vector<int> sortedValue;
    for (auto v : values) {
        sortedValue.push_back(v);
    }
    sort(sortedValue.begin(), sortedValue.end());
    bool isOk = true;
    for (int i = 0; i < sortedValue.size()-1; i++) {
        for (int j = i; j < sortedValue.size();j++) {
            int x = sortedValue[j] / sortedValue[i];
            if (arr[x] !=1) {
                isOk=false;
                break;
            }
        }
    }


    if (isOk) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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