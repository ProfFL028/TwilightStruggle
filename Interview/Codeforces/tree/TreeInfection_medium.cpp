// codeforces:  https://codeforces.com/contest/1665/problem/C

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

int t,n,sz[200100],x;
priority_queue<int> q;
bool f(int x)
{
    for (int i=1;i<=n;i++)
    {
        if (sz[i])q.push(sz[i]);
    }
    int ans=n;

    int sum=x;
    while (!q.empty())
    {
        sum--;
        int o=q.top();
        q.pop();

        ans-=max(0,min(o-1,sum));
    }
    if (ans<=x)return true;
    else return false;
}
int main()
{
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (int i=0;i<=n;i++)
        {
            sz[i]=0;
        }
        sz[0]++;
        for (int i=2;i<=n;i++)
        {
            scanf("%d",&x);
            sz[x]++;
        }

        int l=0,r=n;
        while (l<r)
        {
            int mid=l+r>>1;
            if (f(mid))r=mid;
            else l=mid+1;
        }
        printf("%d\n",r);
    }
}
