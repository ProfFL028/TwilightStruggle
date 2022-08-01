// codeforces: 

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

bool isSame(string s1, int start, string s2) {
    if (start + s2.size() > s1.size()) {
        return false;
    }
    for (int i = 0; i < s2.size(); i++) {
        if (s1[i + start] != s2[i]) {
            return false;
        }
    }
    return true;
}

void solve() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> arr(n);
    vector<pair<int, int>> dest(s.size(), pair<int, int>(0, 0));
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (int j = 0; j < s.length() - arr[i].length() + 1; j++) {
            if (isSame(s, j, arr[i])) {
                for (int k = j; k < j + arr[i].size(); k++) {
                    if (j + arr[i].size() > dest[k].first) {
                        dest[k] = make_pair(j + arr[i].size(), i + 1);
                    }
                }
            }
        }
    }
    int i = 0;
    vector<pair<int, int>> ops;
    while (i < s.size()) {
        if (dest[i].first != 0) {
            ops.emplace_back(dest[i].first - arr[dest[i].second-1].size()+1, dest[i].second);
            i = dest[i].first;
        } else {
            cout << "-1" << endl;
            return ;
        }
    }
    cout << ops.size() << endl;
    for (auto &op: ops) {
        cout << op.second << " " << op.first << endl;
    }
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