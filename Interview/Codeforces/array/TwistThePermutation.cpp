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
    int n;
    cin >> n;
    vector<tuple<int, int>> arr(n);
    for (int i = 0; i < n; i++) {
        tuple<int, int> a;
        cin >> get<0>(a);
        get<1>(a) = i + 1;
        arr[get<0>(a)-1] = a;
    }

    vector<int> ops(n);
    for (int i = n - 1; i >= 0; i--) {
        if (get<1>(arr[i]) == i+1) {
            ops[i] = 0;
        } else {
            int m = get<1>(arr[i]);
            for (int j = 0; j < i; j++) {
                if (get<1>(arr[j]) > m) {
                    get<1>(arr[j]) -= m;
                } else {
                    get<1>(arr[j]) += (i - m + 1);
                }
            }
            ops[i] = m;
        }
    }
    for (auto v : ops) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_TwistPermutation.txt", "r", stdin);
    freopen("../data/output_TwistPermutation.txt", "w", stdout);
    freopen("../data/error_TwistPermutation.txt", "w", stderr);
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