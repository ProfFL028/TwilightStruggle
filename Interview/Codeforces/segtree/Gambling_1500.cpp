// codeforces: https://codeforces.com/contest/1692/problem/H

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
    int n;
    cin >> n;
    vector<int> x(n);
    map<int, vector<int> > p;
    for(int i = 0; i < n; i ++ )
    {
        cin >> x[i];
        p[x[i]].push_back(i);
    }

    int a = x[0], l = 0, r = 1, ans = 1;
    for(auto [b, q] : p)
    {
        int minv = 0, k = q[0];
        for(int j = 0; j < q.size(); j ++ )
        {
            int i = q[j];
            int cur = j - (i - j);
            if(cur < minv)
            {
                minv = cur;
                k = i;
            }
            int res = cur + 1 - minv;
            if(res > ans)
            {
                ans = res;
                a = b;
                l = k;
                r = i + 1;
            }
        }
    }
    cout << a << " " << l + 1 << " " << r << endl;
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