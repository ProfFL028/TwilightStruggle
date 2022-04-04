// codeforces: https://codeforces.com/contest/1660/problem/F1

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

constexpr int MAXN = 4e5 + 10;
int C[3][MAXN];
#define lowbit(x) (x & -x)
inline void Add(int t, int pos, int maxn) {
    for (int i = pos; i <= maxn; i += lowbit(i)) C[t][i]++;
}
inline long long Sum(int t, int pos) {
    long long ans = 0;
    for (int i = pos; i; i -= lowbit(i)) ans += C[t][i];
    return ans;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    int cur = n + 1, maxn = 2 * n + 1;
    for (int i = 0; i <= 2; ++i) for (int j = 1; j <= maxn; ++j) C[i][j] = 0;
    Add(cur % 3, cur, maxn);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '-') cur++;
        else cur--;
        ans += Sum(cur % 3, cur);
        Add(cur % 3, cur, maxn);
    }
    cout << ans << '\n';
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    // freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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