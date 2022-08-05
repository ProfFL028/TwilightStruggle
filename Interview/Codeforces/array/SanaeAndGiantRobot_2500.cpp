// codeforces: https://codeforces.com/contest/1688/problem/F

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 1e9 + 7;
#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

void solve() {
    int n,m,i;
    cin>>n>>m;
    vector<ll> a(n+1);
    vector<int> deg(m,2),b(n+1),id(n+1);
    vector<pair<int,int>> p(m);
    vector<vector<int>> e(n+1);
    iota(id.begin(), id.end(),0);
    set<int> s(id.begin(), id.end());
    for (i=1;i<=n;i++) cin>>a[i];
    for (i=1;i<=n;i++) cin>>b[i];
    for (i=0;i<m;i++)
    {
        auto &[l,r]=p[i];
        cin>>l>>r;
        e[l-1].push_back(i);
        e[r].push_back(i);
    }
    for (i=1;i<=n;i++) a[i]-=b[i];
    for (i=1;i<=n;i++) a[i]+=a[i-1];
    queue<int> q;
    for (i=0;i<=n;i++) if (!a[i]) q.push(i),s.erase(i);
    while (q.size())
    {
        int x=q.front();q.pop();
        for (int y:e[x]) if (!--deg[y])
            {
                auto [l,r]=p[y];
                auto lt=s.lower_bound(l),rt=s.upper_bound(r);
                for (auto it=lt;it!=rt;++it) q.push(*it);
                s.erase(lt,rt);
            }
    }
    cout<<(s.size()?"NO\n":"YES\n");
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