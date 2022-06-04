// codeforces: https://codeforces.com/contest/1691/problem/E

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

struct DSU{
    vector<int> dsu, szx;

    DSU() = default;
    DSU(int n) : dsu(n), szx(n, 1) {
        for(int i=0; i<n; i++) dsu[i] = i;
    }

    int parent(int i){
        if(dsu[i]==i) return i;
        else return dsu[i] = parent(dsu[i]);
    }

    int size(int i) { return szx[parent(i)]; }
    int operator[](int i){ return parent(i); }
    int num_comps(){
        int ct = 0;
        for(int i=0; i<dsu.size(); i++) if(dsu[i] == i) ct++;
        return ct;
    }

    void unify(int a, int b){
        a = parent(a);
        b = parent(b);
        if(szx[a] < szx[b]) swap(a, b);
        if(a!=b) dsu[b] = a, szx[a] += szx[b];
    }
};

struct Point {
    int color, start, end, id;
    bool closed;

    bool operator<(const Point &x) const {
        if (start == x.start) return closed <= x.closed;
        return start < x.start;
    }
};

void solve() {
    int n; cin>>n;
    vector<Point> points;
    for(int i=0; i<n; i++){
        int t, l, r; cin>>t>>l>>r;
        points.push_back({t, l, r, i, false});
        points.push_back({t, r, l, i, true});
    }
    sort(points.begin(), points.end());

    DSU dsu(n);
    vector<set<pair<int, int>>> open(2); // {r, id}
    for(auto &p:points){
        if(p.closed) open[p.color].erase({p.start, p.id});
        else{
            open[p.color].insert({p.end, p.id});
            while(open[p.color ^ 1].size() > 1){
                auto [r, id] = *open[p.color^ 1].begin();
                dsu.unify(p.id, id);
                open[p.color ^ 1].erase({r, id});
            }
            if(open[p.color ^ 1].size() == 1) dsu.unify(p.id, open[p.color ^ 1].begin()->second);
        }
    }

    cout<<dsu.num_comps()<<endl;
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