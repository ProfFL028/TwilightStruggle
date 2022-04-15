#include<bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef long long LL;
typedef long double LD;
typedef pair<int,int> PII;

const int N=500010,M=18,mod=998244353;

struct node{
    int l,r,sz;
    int s[2][3];
    bool g[3][3],st[2];
}tr[4*N];
char str[3][N];
int p[20],n,m;

int get_id(int x,int y,int z){
    return x*6+y*3+z+1;
}

int find(int x){
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}

int find(int a,int b,int c){
    return find(get_id(a,b,c));
}

void push_up(node &mid,node l,node r){
    mid.sz=l.sz+r.sz;
    for(int i=0;i<3;i++){
        mid.s[0][i]=l.s[0][i];
        mid.s[1][i]=r.s[1][i];
    }
    for(int i=0;i<=13;i++) p[i]=i;
    for(int i=0;i<2;i++){
        if(l.st[i]){
            int a=find(0,i,0),b=find(0,i,2);
            if(a!=b) p[b]=a;
        }
        if(r.st[i]){
            int a=find(1,i,0),b=find(1,i,2);
            if(a!=b) p[b]=a;
        }
    }
    for(int i=0;i<2;i++){
        if(l.s[0][i] && l.s[0][i+1]){
            int a=find(0,0,i),b=find(0,0,i+1);
            if(a!=b) p[b]=a;
        }
        if(l.s[1][i] && l.s[1][i+1]){
            int a=find(0,1,i),b=find(0,1,i+1);
            if(a!=b) p[b]=a;
        }
        if(r.s[0][i] && r.s[0][i+1]){
            int a=find(1,0,i),b=find(1,0,i+1);
            if(a!=b) p[b]=a;
        }
        if(r.s[1][i] && r.s[1][i+1]){
            int a=find(1,1,i),b=find(1,1,i+1);
            if(a!=b) p[b]=a;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(l.g[i][j]){
                int a=find(0,0,i),b=find(0,1,j);
                if(a!=b) p[b]=a;
            }
            if(r.g[i][j]){
                int a=find(1,0,i),b=find(1,1,j);
                if(a!=b) p[b]=a;
            }
        }
    }
    for(int i=0;i<3;i++){
        if(l.s[1][i] && r.s[0][i]){
            int a=find(0,1,i),b=find(1,0,i);
            if(a!=b) mid.sz--,p[b]=a;
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int a=find(0,0,i),b=find(1,1,j);
            if(a==b) mid.g[i][j]=1;
            else mid.g[i][j]=0;
        }
    }
    if(find(0,0,0)==find(0,0,2)) mid.st[0]=1;
    else mid.st[0]=0;
    if(find(1,1,0)==find(1,1,2)) mid.st[1]=1;
    else mid.st[1]=0;
}

void push_up(int u){
    push_up(tr[u],tr[u<<1],tr[u<<1|1]);
}

void build(int u,int l,int r){
    tr[u]={l,r};
    if(l==r){
        tr[u].s[0][0]=tr[u].s[1][0]=str[0][l]-'0';
        tr[u].s[0][1]=tr[u].s[1][1]=str[1][l]-'0';
        tr[u].s[0][2]=tr[u].s[1][2]=str[2][l]-'0';
        int t=0;
        for(int i=2;i>=0;i--) t=t*2+tr[u].s[0][i];
        if(t==0){
            tr[u].sz=0;
        }if(t==1){
            tr[u].sz=1;
            tr[u].g[0][0]=1;
        }else if(t==2){
            tr[u].sz=1;
            tr[u].g[1][1]=1;
        }else if(t==4){
            tr[u].sz=1;
            tr[u].g[2][2]=1;
        }else if(t==3){
            tr[u].sz=1;
            tr[u].g[0][0]=tr[u].g[1][1]=tr[u].g[0][1]=tr[u].g[1][0]=1;
        }else if(t==5){
            tr[u].sz=2;
            tr[u].g[0][0]=tr[u].g[2][2]=1;
        }else if(t==6){
            tr[u].sz=1;
            tr[u].g[1][1]=tr[u].g[2][2]=tr[u].g[1][2]=tr[u].g[2][1]=1;
        }else if(t==7){
            tr[u].sz=1;
            tr[u].g[0][0]=tr[u].g[0][1]=tr[u].g[0][2]=1;
            tr[u].g[1][0]=tr[u].g[1][1]=tr[u].g[1][2]=1;
            tr[u].g[2][0]=tr[u].g[2][1]=tr[u].g[2][2]=1;
            tr[u].st[0]=tr[u].st[1]=1;
        }
        return ;
    }
    int mid=(l+r)/2;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    push_up(u);
    //cout<<l<<' '<<r<<' '<<tr[u].sz<<endl;
}

node query(int u,int l,int r){
    if(l<=tr[u].l && tr[u].r<=r) return tr[u];
    int mid=(tr[u].l+tr[u].r)/2;
    if(r<=mid)  return query(u<<1,l,r);
    if(l>mid) return query(u<<1|1,l,r);
    node res;
    push_up(res,query(u<<1,l,r),query(u<<1|1,l,r));
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<3;i++) scanf("%s",str[i]+1);
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        printf("%d\n",query(1,l,r).sz);
    }
    return 0;
}




//E

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MX 500006
#define PI pair<int, int>
vector<int> p(3 * MX + 1);
inline int getp(int r){
    return r == p[r] ? r : p[r] = getp(p[r]);
}
inline bool uni(int x, int y){
    x = getp(x); y = getp(y);
    if(x == y){
        return false;
    }
    p[y] = x;
    return true;
}
int main(){
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> s(4);
    vector<int> pre(n + 1);
    for(int i = 0; i < 3; i++){
        cin >> s[i];
    }
    for(int i = 0; i < n; i++){
        pre[i + 1] += pre[i];
        for(int j = 0; j < 3; j++){
            pre[1 + i] += s[j][i] - '0';
        }
    }
    for(int i = 0; i < 3 * n + 1; i++){
        p[i] = i;
    }
    vector<int> prhe(n + 1, 0), prve(n + 1, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            if(s[j][i] == '1' && s[j + 1][i] == '1' && uni(j * n + i, (j + 1) * n + i)){
                ++prve[i + 1];
            }
        }
        if(i == 0) continue;
        for(int j = 0; j < 3; j++){
            if(s[j][i] == '1' && s[j][i - 1] == '1' && uni(j * n + i, (i - 1) + j * n)){
                ++prhe[i];
            }
        }
    }
    for(int i = 0; i < n; i++){
        prve[i + 1] += prve[i];
        prhe[i + 1] += prhe[i];
    }
    vector<int> nxt(n + 1, 0);
    for(int i = n - 1; i >= 0; i--){
        nxt[i] = (s[0][i] == '1' && s[1][i] == '0' && s[2][i] == '1' ? (nxt[i + 1] + 1) : 0);
    }
    int m;
    cin >> m;
    while(m--){
        int l,r;
        cin >> l >> r;
        --l; --r;
        int non101 = l + nxt[l];
        if (non101 > r){
            cout << "2\n";
            continue;
        }
        int tot = pre[r + 1] - pre[non101];
        int in = (prve[r + 1] - prve[non101]) + (prhe[r] - prhe[non101]);
        int res = tot - in;
        if (non101 != l){
            if (s[0][non101] == '1' && s[1][non101] == '1' && s[2][non101] == '1');
            else if (s[0][non101] == '0' && s[2][non101] == '0') res += 2;
            else ++res;
        }
        cout << res << "\n";
    }
}