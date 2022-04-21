// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/H

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n;
    cin >> n;
    map<int, int> seller;
    set<int> p;
    for (ll i = 0; i < n; i++) {
        int x;
        cin >> x;
        seller[x]++;
        p.insert(x);
    }
    int m;
    cin >> m;
    map<int, int> buyer;
    for (ll i = 0; i < m;i++) {
        int x;
        cin >> x;
        buyer[x]++;
        p.insert(x);
    }

    vector<int> vp;
    int sellerPre = 0, buyerPre = 0;
    for (auto & k : p) {
        vp.push_back(k);
        seller[k] += sellerPre;
        sellerPre = seller[k];
        int tmp = buyer[k];
        buyer[k] = m - buyerPre;
        buyerPre += tmp;
    }

    ll ans = 0;
    for(auto& price : p) {
        ll cur = 1ll * price * (min(seller[price], buyer[price]));
        if (cur > ans) {
            ans = cur;
        }
    }

    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
#endif
    fast()

    int testCase = 1;
    // cin >> testCase;
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