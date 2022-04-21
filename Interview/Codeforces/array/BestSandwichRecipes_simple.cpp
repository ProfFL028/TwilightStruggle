// codeforces: https://starcontest22.contest.codeforces.com/group/ZbfYu7B821/contest/378187/problem/J

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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> bread(n);
    for (int i = 0; i < n; i++) {
        cin >> bread[i];
    }
    vector<int> cheese(m);
    for (int i = 0; i < m; i++) {
        cin >> cheese[i];
    }
    vector<int> sausage(k);
    for (int i = 0; i < k; i++) {
        cin >> sausage[i];
    }

    sort(bread.begin(), bread.end());
    sort(cheese.begin(), cheese.end());
    sort(sausage.begin(), sausage.end());

    int ans = 0;
    int c = 0, s = 0;
    int cheeseSize = cheese.size();
    int sausageSize = sausage.size();
    for (auto &b: bread) {
        int preC = c;
        while (c < cheeseSize && cheese[c++] <= b);
        if (!(c > preC && cheese[c - 1] > b)) break;
        int cc = cheese[c - 1];
        int preS = s;
        while (s < sausageSize && sausage[s++] <= cc);
        if (s > preS && sausage[s - 1] > cc) {
            ans++;
        }
        if (c == cheeseSize) break;
        if (s == sausageSize) break;
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