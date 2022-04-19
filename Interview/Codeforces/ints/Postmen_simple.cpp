// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/G

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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> postmen(3, vector<int>());
    set<set<int>> black;
    for (int i = 0; i < n; i++) {
        int tp, m;
        cin >> tp >> m;
        set<int> unknown;
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            if (tp == 0) {
                postmen[0].push_back(x);
            } else {
                unknown.insert(x);
            }
        }
        black.insert(unknown);
    }
    for (auto& s : black) {
        vector<int> t;
        for (auto& x : s) {
            if (std::find(postmen[0].begin(), postmen[0].end(), x) == postmen[0].end()) {
                t.push_back(x);
            }
        }
        if (t.size() == 1) {
            postmen[1].push_back(t[0]);
        }
    }

    int c0 = postmen[0].size();
    int c1 = postmen[1].size();
    int c2 = k - c0 - c1;
    cout << c0 << " "<< c1 <<" "<< c2;
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