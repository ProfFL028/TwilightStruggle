// codeforces:  https://codeforces.com/contest/1673/problem/C

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

const ll MOD = 10e9 + 7;
const int MAX_SIZE = 4 * 10e4 + 10;

vector<int> dp(MAX_SIZE,0);

void solve() {
    int n;
    cin >> n;

    int ans = dp[n];
    cout << ans << endl;
}

void init() {
    int  i, j;
    vector <int> d;
    for (i = 1; i <= MAX_SIZE; i++)
    {
        string s = to_string(i);
        string t = s;
        reverse(t.begin(), t.end());
        if (s == t)
            d.push_back(i);
    }
    dp[0] = 1;
    for (auto i : d)
    {
        for (j = i; j <= 4e4; j++)
        {
            dp[j] += dp[j - i];
            dp[j] %= MOD;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
#endif
    fast()
    init();

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