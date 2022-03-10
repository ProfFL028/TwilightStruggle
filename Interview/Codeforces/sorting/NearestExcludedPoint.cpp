#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
//#define int long long
using ll=long long;
void debug() { cerr << endl; } template <typename T, typename... Ts> void debug(T x, Ts... y) { cerr << "\033[31m" << x << "\033[0m"; if (sizeof...(y) > 0) cerr << ' '; debug(y...); } template <typename T> void debug(const T& a, int l, int r, char c) { for (int i = l; i <= r; ++i) cerr << "\033[31m" << a[i] << "\033[0m" << (i == r ? '\n' : c); } template <typename T> void debug(vector<T> a) { for (int i = 0; i < (int)a.size(); ++i) cerr << "\033[31m" << a[i] << "\033[31m" << " \n"[i == ((int)a.size() - 1)]; }


map<int,int>mp[200005];
int dir[4][2]={-1,0,1,0,0,1,0,-1};
pair<int,int>point[200005];
pair<int,int>ans[200005];
signed main() {
    //ofstream cout("E:\\acm dream\\out.out");
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#ifdef BADDOG_LOCAL
    //ifstream cin("E:\\acm dream\\in.in");
  double be = clock();
#endif

    int n;cin>>n;
    for(int i=0;i<n;++i)ans[i]=make_pair(1e9,1e9);
    for(int i=0;i<n;++i){
        int x,y;cin>>x>>y;
        mp[x][y]=i;
        point[i]=make_pair(x,y);
    }
    vector<int>d(n);
    queue<int>q;
    vector<int>vis(n);
    for(int i=0;i<n;++i){
        for(int k=0;k<4;++k){
            int nx=point[i].first+dir[k][0];
            int ny=point[i].second+dir[k][1];
            if(!mp[nx].count(ny)){
                q.push(i);
                vis[i]=1;
                ans[i]=make_pair(nx,ny);
                break;
            }
        }
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        int x=point[u].first,y=point[u].second;
        for(int i=0;i<4;++i){
            int nx=x+dir[i][0],ny=y+dir[i][1];
            if(mp[nx].count(ny)&&!vis[mp[nx][ny]]){
                q.push(mp[nx][ny]);
                vis[mp[nx][ny]]=1;
                ans[mp[nx][ny]]=ans[u];
            }
        }
    }
    for(int i=0;i<n;++i)cout<<ans[i].first<<' '<<ans[i].second<<endl;

#ifdef BADDOG_LOCAL
    double en = clock();
  cout<<"\ntime: "<<fixed<<setprecision(8)<<en-be;
#endif
    return 0;
}
// init?
// var->0?
// infinite dfs?
// out of bound?
// max_element / min_element?