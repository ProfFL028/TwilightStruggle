// codeforces: https://codeforces.com/contest/1661/problem/E

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
#define MX 500006
vector<int> p(3 * MX + 1);
// get marked position
inline int getp(int r){
    return r == p[r] ? r : p[r] = getp(p[r]);
}
// if x and y are marked, we will not count it anymore. Fix 111 101 111 problem.
inline bool uni(int x, int y){
    x = getp(x); y = getp(y);
    if(x == y){
        return false;
    }
    p[y] = x;
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<string> s(4);
    vector<int> pre(n + 1);
    for(int i = 0; i < 3; i++){
        cin >> s[i];
    }
    // pre: one count from left to right.
    for(int i = 0; i < n; i++){
        pre[i + 1] += pre[i];
        for(int j = 0; j < 3; j++){
            pre[1 + i] += s[j][i] - '0';
        }
    }
    for(int i = 0; i < 3 * n + 1; i++){
        p[i] = i;
    }
    /**
     * prhe: connected 1 count in horizontal.
     * prve: connected 1 count in vertical.
     */
    vector<int> prhe(n + 1, 0), prve(n + 1, 0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            if(s[j][i] == '1' && s[j + 1][i] == '1' && uni(j * n + i, (j + 1) * n + i)){
                ++prve[i + 1];
            }
        }
        if(i == 0) continue;
        for(int j = 0; j < 3; j++){
            if(s[j][i] == '1' && s[j][i - 1] == '1' && uni(j * n + i, (i - 1) + j * n)){
                ++prhe[i];
            }
        }
    }
    for(int i = 0; i < n; i++){
        prve[i + 1] += prve[i];
        prhe[i + 1] += prhe[i];
    }
    vector<int> nxt(n + 1, 0);
    for(int i = n - 1; i >= 0; i--){
        nxt[i] = (s[0][i] == '1' && s[1][i] == '0' && s[2][i] == '1' ? (nxt[i + 1] + 1) : 0);
    }
    int m;
    cin >> m;
    while(m--){
        int l,r;
        cin >> l >> r;
        --l; --r;
        /**
         * makesure 101 is not at the front.
         */
        int non101 = l + nxt[l];
        if (non101 > r){
            cout << "2\n";
            continue;
        }
        // ans = total 1 count - connected 1 count
        int tot = pre[r + 1] - pre[non101];
        int in = (prve[r + 1] - prve[non101]) + (prhe[r] - prhe[non101]);
        int res = tot - in;
        /**
         * If left=101 we need to add extra 1 counts.
         */
        if (non101 != l){
            if (s[0][non101] == '1' && s[1][non101] == '1' && s[2][non101] == '1');
            else if (s[0][non101] == '0' && s[2][non101] == '0') res += 2;
            else ++res;
        }
        cout << res << "\n";
    }
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