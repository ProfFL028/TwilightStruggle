// codeforces: 

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
    string str;
    int value;
    cin >> str >> value;
    map<int, deque<int>> m;
    for (int i = 0, len = str.length(); i < len; i++) {
        int v = str[i] - 'a' + 1;
        m[v].push_back(i);
    }
    int cur = 1;
    vector<int> usePos;
    int total = 0;
    bool isOK = false;
    while (cur <= 26 && !isOK) {
        if (m.contains(cur)) {
            auto & queue = m[cur];
            while (!queue.empty()) {
                if (total + cur <= value) {
                    total += cur;
                    usePos.push_back(queue.front());
                    queue.pop_front();
                } else {
                    isOK = true;
                    break;
                }
            }
        }
        cur++;
    }
    sort(usePos.begin(), usePos.end());
    for (auto i : usePos) {
        cout << str[i];
    }
    cout << endl;
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