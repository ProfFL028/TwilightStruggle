// codeforces: https://codeforces.com/contest/1662/problem/D

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

string findRoot(string x) {
    string root;
    int bCount = 0;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == 'B')
            bCount++;
        else {
            root.push_back(x[i]);
        }
    }

    bool removed = true;
    while (removed) {
        int n = root.size();
        removed = false;
        for (int i = 0; i < n - 1; i++) {
            if (root[i] == root[i+1]) {
                root.erase(root.begin() + i);
                root.erase(root.begin() + i);
                removed = true;
                break;
            }
        }
    }

    if (bCount % 2 == 0) {
        root.push_back('B');
    }

    return root;
}

void solve() {
    string a, b;
    cin >> a >> b;

    string rootA = findRoot(a);
    string rootB = findRoot(b);
    if (rootA == rootB) {
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