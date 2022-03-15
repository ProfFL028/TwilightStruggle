#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+1e3;
int tot,n,q,mod;
int f[N],a[N],b[N],c[N],d[N];
void add(int x,int val)
{
    if(val==0||x>n||x<0)return;
    if(d[x]==0)tot--;
    d[x]=((d[x]+val)%mod+mod)%mod;
    if(d[x]==0)tot++;
}
signed main()
{
    scanf("%lld%lld%lld",&n,&q,&mod);
    f[1]=f[2]=1;
    for(int i=3;i<=n+10;i++)f[i]=(f[i-1]+f[i-2])%mod;
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
    for(int i=1;i<=n;i++)c[i]=(a[i]-b[i]+mod)%mod;
    tot=0;
    for(int i=1;i<=n;i++)
        tot++,add(i,c[i]-c[i-1]-c[max(0ll,i-2)]);
    while(q--)
    {
        char s[10];int l,r;
        scanf("%s%lld%lld",s+1,&l,&r);
        if(s[1]=='A'){add(l,1);add(r+1,-f[r-l+2]);add(r+2,-f[r-l+1]);}
        else {add(l,-1);add(r+1,f[r-l+2]);add(r+2,f[r-l+1]);}
        puts(tot==n?"YES":"NO");
    }
    return 0;
}
/*
差分定义为 di=ai-a{i-1}-a{i-2}，妙啊！
因为题目要求的是全 0，所以没有影响。
*/