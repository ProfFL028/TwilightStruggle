#include <bits/stdc++.h>

using namespace std;

template <typename T, class F = function<T(const T&, const T&)>>
class segtree {
private:
    int n;
    vector<T> tree;
    F func;
    const T out;

public:
    segtree(vector<T>& a, const F& f, const T _out) : func(f), out(_out) {
        n = (int) a.size();
        tree.assign(n << 1, out);
        copy(a.begin(), a.end(), tree.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    void update(int i, const T v) {
        i += n;
        tree[i] = v;
        while(i > 0) {
            i >>= 1;
            tree[i] = func(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    T query(int l, int r) {
        T res = out;
        l += n, r += n;
        while (l <= r) {
            if (l & 1) { // odd
                res = func(res, tree[l++]);
            }
            if (r & 1 ^ 1) { // even
                res = func(res, tree[r--]);
            }
            l >>= 1, r >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first;
            a[i].second = i;
        }
        const int INF = 1 << 30;
        segtree<pair<int, int>> s(a, [](pair<int, int> x, pair<int, int> y) { return min(x, y); }, {INF, -1});
        int q;
        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            vector<int> v;
            // 取31个最小值。
            for (int i = 0; i <= 30; i++) {
                pair<int, int> x = s.query(l, r);
                if (x.first == INF) {
                    break;
                }
                s.update(x.second, {INF, x.second});
                v.push_back(x.second);
            }
            for (int i : v) { // fixing
                s.update(i, {a[i].first, i});
            }
            int ans = INF;
            for (int i = 0; i < v.size(); i++) {
                for (int j = i + 1; j < v.size(); j++) {
                    ans = min(ans, a[v[i]].first | a[v[j]].first);
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
