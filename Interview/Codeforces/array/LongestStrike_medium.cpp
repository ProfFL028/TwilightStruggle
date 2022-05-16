// codeforces: https://codeforces.com/contest/1676/problem/F

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
    int n, k;
    cin >> n >> k;
    int a[n];
    map<int, int> mp;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]]++;
    }
    vector<int> c;
    for(auto x : mp)
    {
        if(x.second >= k)
        {
            c.push_back(x.first);
        }
    }
    if(c.size() == 0)
    {
        cout << -1 << endl;
        return;
    }
    sort(c.begin(), c.end());
    int mx = 0;
    int lans = c[0], rans = c[0];
    int l = c[0];
    for(int i = 1; i < c.size(); i++)
    {
        if(c[i]-1 == c[i-1])
        {
            if(c[i]-l > mx)
            {
                lans = l;
                rans = c[i];
                mx = c[i]-l;
            }
        }
        else
        {
            l = c[i];
        }
    }
    cout << lans << " " << rans << endl;
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