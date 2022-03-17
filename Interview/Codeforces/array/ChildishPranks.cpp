#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n, m;
    cin >> n >> m;
    char  a[1000][1000];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    if (a[0][0] == '1') {
        cout << -1 << endl;
        return;
    }
    vector<tuple<int, int, int, int>> answer;
    for (int i = n - 1; i > 0; --i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '1') {
                answer.push_back(tuple<int, int, int, int>(i, j + 1, i + 1, j + 1));
            }
        }
    }
    for (int j = m - 1; j > 0; --j) {
        if (a[0][j] == '1') {
            answer.push_back(tuple<int, int, int, int>(1, j, 1, j + 1));
        }
    }
    cout << answer.size() << endl;
    for (const auto &a: answer) {
        cout << get<0>(a) << " " << get<1>(a) << " "
             << get<2>(a) << " " << get<3>(a) << " "
             << endl;
    }

}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_CP.txt", "r", stdin);
    freopen("../data/output_CP.txt", "w", stdout);
    freopen("../data/error_CP.txt", "w", stderr);
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