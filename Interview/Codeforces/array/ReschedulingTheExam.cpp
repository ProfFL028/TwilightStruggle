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
    ll len, total;
    cin >> len >> total;
    vector<ll> exam(len);

    ll min, minIndex;
    cin >> exam[0];
    min = exam[0];
    minIndex = 0;
    for (int i = 1; i < len; i++) {
        cin >> exam[i];
        if (exam[i] - exam[i - 1] < min) {
            min = exam[i] - exam[i - 1];
            minIndex = i;
        }
    }


}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_ReschedulingTheExam.txt", "r", stdin);
    freopen("../data/output_ReschedulingTheExam.txt", "w", stdout);
    freopen("../data/error_ReschedulingTheExam.txt", "w", stderr);
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