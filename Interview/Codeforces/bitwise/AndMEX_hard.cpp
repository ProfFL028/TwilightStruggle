// codeforces:   https://codeforces.com/contest/1659/problem/E

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

class DSU {
private:
    vector<int> parent;
public:
    DSU(int n) {
        parent = vector<int>(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int getRoot(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }

    bool sameRoot(int p1, int p2) {
        return getRoot(p1) == getRoot(p2);
    }

    bool merge(int p1, int p2) {
        p1 = getRoot(p1);
        p2 = getRoot(p2);
        if (p1 == p2)
            return false;
        parent[p2] = p1;
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<DSU> dsu(32, DSU(n));
    vector<bool> can1(n + 1, 0);
    vector<vector<bool>> query(32, vector<bool>(n + 1, 0));
    while (m--) {
        ll l, r, v;
        cin >> l >> r >> v;
        if (v & 1 ^ 1) {
            can1[l] = can1[r] = true;
        }
        for (int i = 0; i < 30; i++) {
            if (v >> i & 1) {
                dsu[i].merge(l, r);
            }
        }
    }

    for (int i = 1; i < n + 1; i++) {
        if (can1[i]) {
            for (int j = 0; j < 30; j++) {
                query[j][dsu[j].getRoot(i)] = true;
            }
        }
    }

    ll q;
    cin >> q;
    while (q--) {
        int ans = 2;
        int l, r;
        cin >> l >> r;
        for (int i = 0; i < 30; i++) {
            if (dsu[i].sameRoot(l, r)) {
                ans = 0;
                break;
            }
        }
        if (ans == 0) {
            cout << ans << endl;
            continue;
        }
        for (int i = 1; i < 30; i++) {
            if (query[i][dsu[i].getRoot(l)] == 1) {
                ans = 1;
                break;
            }
        }
        cout << ans << endl;
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