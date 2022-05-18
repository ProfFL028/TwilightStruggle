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

const ll MOD = 1e9 + 7;
const int MAX_SIZE = 40004;


vector<int> palindromes;
vector<ll> dp(MAX_SIZE, 0);

void solve() {
    int n;
    cin >> n;


    cout << dp[n] << endl;
}

void init() {
    for (int i = 1; i < MAX_SIZE; i++) {
        string s = to_string(i);
        bool ok = true;
        for (int j = 0; j < s.size() / 2; j++) {
            if (s[j] != s[s.size() - 1 - j]) {
                ok = false;
                break;
            }
        }
        if (ok)
            palindromes.push_back(i);
    }

    int m = palindromes.size();

    dp[0] = 1;
    for (int i = 0; i < m; ++i) {
        for (int j = 1; j < MAX_SIZE; j++) {
            if (j < palindromes[i]) continue;
            dp[j] += dp[j - palindromes[i]];
            dp[j] %= MOD;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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