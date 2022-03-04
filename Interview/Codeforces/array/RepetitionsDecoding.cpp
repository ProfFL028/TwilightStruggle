#include<iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int len;
    cin >> len;
    vector<ll> arr(len, 0);
    map<ll, int> eleCount;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
        if (eleCount.find(arr[i]) != eleCount.end()) {
            eleCount[arr[i]] += 1;
        } else {
            eleCount.insert(pair<ll, int>(arr[i], 1));
        }
    }
    for (const auto &item: eleCount) {
        if (item.second % 2 != 0) {
            cout << -1 << endl;
            return;
        }
    }

    int i = 1;
    int preIdx = 0;
    vector<tuple<int, ll> > ops;
    vector<int> splitArr;
    while (i < arr.size()) {
        if (arr[i] == arr[preIdx]) {
            splitArr.push_back((i - preIdx) * 2);
            int samePos = i++;
            for (++preIdx; preIdx < samePos; preIdx++) {
                if (i < arr.size() && arr[i] != arr[preIdx]) {
                    ops.emplace_back(i, arr[preIdx]);
                    arr.insert(arr.begin() + i, arr[preIdx]);
                    arr.insert(arr.begin() + i, arr[preIdx]);
                }
                i++;
            }
            preIdx = i;
        }
        i++;
    }
    cout << ops.size() << endl;
    for (const auto &item: ops) {
        cout << get<0>(item) << ", " << get<1>(item) << endl;
    }
    cout << splitArr.size() << endl;
    for (const auto &item: splitArr) {
        cout << item << " ";
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_RepetitionsDecoding.txt", "r", stdin);
    freopen("../data/output_RepetitionsDecoding.txt", "w", stdout);
    freopen("../data/error_RepetitionsDecoding.txt", "w", stderr);
#endif
    fast()

    int testCase = 0;
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