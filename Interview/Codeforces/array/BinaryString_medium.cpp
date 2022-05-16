// codeforces:  https://codeforces.com/contest/1680/problem/C

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

void solve() {
    string s;
    cin>>s;
    ll zero = 0, one = 0, ret = s.size();
    for(int i = 0; i < s.size(); i++) {
        if (s[i] == '0') zero++;
        else one++;
    }
    // max of 0's in window, or 1's outside window
    // score is min when z <= o
    ll z = 0, o = one, j = 0;
    for(int i = 0; i < s.size(); i++) {
        while(j < s.size() && z < o) {
            if (s[j] == '0') {
                z++;
            } else {
                o--;
            }
            j++;
        }
        ret = min(ret, max(z,o));
        if (s[i] == '0') z--;
        else o++;
    }
    cout <<ret << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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