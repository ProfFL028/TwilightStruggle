#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>
#define MEM(obj) (int)sizeof(obj)
#define REP(i,l,r) for(int i=l;i<r;i++)
using namespace std;
template<typename T>void sa(T&s){for(auto e:s)cout<<e<<" ";}

const int INF = 0x3f3f3f3f;
int main() {
    ios::sync_with_stdio(0); //cin.tie(nullptr);
    int tt; cin >> tt;
    while (tt--) {
        int n, m; cin >> n >> m;
        vector<int> ddl(n+1);
        vector<vector<int>> opts(n+1);
        vector<int> t(m), p(m);
        REP(i,1,n+1) cin >> ddl[i];
        REP(i,0,m) {
            int e;
            cin >> e >> t[i] >> p[i];
            opts[e].push_back(i);
        }
        //solve
        vector<int> a;
        int cur = 0; bool ok = true;
        REP(i,1,n+1) {
            auto opt = opts[i]; int sz = opt.size();
            if (sz == 0) { ok = false; break; }
            vector<vector<int>> dp(sz, vector<int>(105, INF));
            REP(i,1,p[opt[0]]+1) dp[0][i] = t[opt[0]];
            REP(i,0,sz) dp[i][0] = 0;
            REP(i,1,sz) {
                int op = opt[i];
                REP(j,0,101) dp[i][j] = min(dp[i-1][j], dp[i-1][max(0, j-p[op])]+t[op]);
            }
            if (dp[sz-1][100] > 1e9 || cur+dp[sz-1][100] > ddl[i]) { ok = false; break; }
            else cur += dp[sz-1][100];
            for (int i = sz-1, j = 100, op = opt[i]; i >= 0 && j >= 0; op = opt[--i])
                if (i == 0 && j) {
                    a.push_back(opt[0]+1);
                } else
                if (i && dp[i][j] == dp[i-1][max(0,j-p[op])]+t[op]) {
                    a.push_back(op+1); j -= p[op];
                }
        }
        if (ok) {
            cout << a.size() << endl;
            REP(i,0,a.size()) cout << a[i] << " ";
        } else cout << -1;
        cout <<"\n";
    }
    return 0;
}