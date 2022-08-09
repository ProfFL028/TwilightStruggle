#include <bits/stdc++.h>

using namespace std;
const int nax = (int) 2e5 + 47;
const int INF = (int) 1e9 + 47;
const int MOD = 998244353;
const long long LINF = 1e15 + 47;
const int sq = 320;

struct segment_Tree {
    vector<pair<int, int>> t;
    int size;

    void init(int n) {
        size = 1;
        while (size < n)size *= 2;
        t.assign(2 * size - 1, {-INF, 0});
    }

    pair<int, int> get(int v, int tl, int tr, int l, int r) {
        if (l >= tr || r <= tl)return {-INF, tl};
        if (tl >= l && tr <= r)return t[v];
        int tm = (tl + tr) / 2;
        auto s1 = get(v * 2 + 1, tl, tm, l, r);
        auto s2 = get(v * 2 + 2, tm, tr, l, r);
        return max(s1, s2);
    }

    pair<int, int> get(int l, int r) {
        return get(0, 0, size, l, r);
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tr - tl == 1) {
            t[v] = {val, pos};
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos < tm) {
            update(v * 2 + 1, tl, tm, pos, val);
        } else {
            update(v * 2 + 2, tm, tr, pos, val);
        }
        t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
    }

    void update(int pos, int val) {
        update(0, 0, size, pos, val);
    }
};

int q[nax];
int d[nax];

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt;
    cin >> tt;
    for (int test = 1; test <= tt; test++) {
        int n, a, b;
        cin >> n >> a >> b;
        --a, --b;
        vector<int> p(n);
        segment_Tree sg1, sg2;
        sg1.init(n);
        sg2.init(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            sg1.update(i, i + p[i]);
            sg2.update(i, p[i] + (n - i - 1));
        }
        int ql = 0, qr = 1;
        q[ql] = a;
        d[a] = 0;
        sg1.update(a, -INF);
        sg2.update(a, -INF);
        while (ql != qr) {
            int v = q[ql++];
            while (true) {
                auto x = sg2.get(v + 1, min(n, v + p[v] + 1));
                if (x.first == -INF || abs(v - x.second) > min(p[v], p[x.second]))break;
                q[qr++] = x.second;
                d[x.second] = d[v] + 1;
                sg2.update(x.second, -INF);
                sg1.update(x.second, -INF);
            }
            while (true) {
                auto x = sg1.get(max(0, v - p[v]), v);
                if (x.first == -INF || abs(v - x.second) > min(p[v], p[x.second]))break;
                q[qr++] = x.second;
                d[x.second] = d[v] + 1;
                sg1.update(x.second, -INF);
                sg2.update(x.second, -INF);
            }
        }

        cout << d[b] << '\n';
    }


}