// codeforces:  https://codeforces.com/contest/1679/problem/C
// segment tree.
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

template<typename T, class F=function<T(const T &, const T &)>>
class SegTree {
private:
    int n;
    vector<T> tree;
    F func;
    T out;

public:
    SegTree(vector<T> &a, T _out, F f) : func(f), out(_out) {
        n = a.size();
        tree.assign(2 * n, out);
        copy(a.begin(), a.end(), tree.begin() + n);
        for (int i = n - 1; i >= 0; --i) {
            tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void update(int idx, T v) {
        idx += n;
        tree[idx] = v;
        while (idx > 0) {
            idx >>= 1;
            tree[idx] = func(tree[idx << 1], tree[idx << 1 | 1]);
        }
    }

    T query(int l, int r) {
        T res = out;
        l += n;
        r += n;
        while (l <= r) {
            if (l & 1) {
                res = func(res, tree[l++]);
            }
            if (r & 1 ^ 1) {
                res = func(res, tree[r--]);
            }
            l >>= 1;
            r >>= 1;
        }
        return res;
    }

};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1, 0), h(n + 1, 0);
    SegTree<int> sv(v, 1, [](int x, int y) { return x > 0 && y > 0; });
    SegTree<int> sh(h, 1, [](int x, int y) { return x > 0 && y > 0; });
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            v[x]++;
            h[y]++;
            sv.update(x, v[x]);
            sh.update(y, h[y]);
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            v[x]--;
            h[y]--;
            sv.update(x, v[x]);
            sh.update(y, h[y]);
        } else if (t == 3) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            if (sv.query(a, c) || sh.query(b, d)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
         }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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