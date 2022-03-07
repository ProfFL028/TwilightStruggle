/**
 * https://codeforces.com/contest/1646/problem/B
 */
#include<iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int arrSize;
    cin >> arrSize;
    ll arr[arrSize];
    for (int i = 0; i < arrSize; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + arrSize);
    int i = 0;
    int j = arrSize - 1;
    ll sumBlue = arr[0] + arr[1];
    ll sumRed = arr[j];
    i = 2;
    j--;
    bool ok = sumBlue < sumRed;
    while (!ok && i < j) {
        sumBlue += arr[i++];
        sumRed += arr[j--];
        ok = sumBlue < sumRed;
    }
    cout << (ok ? "YES" : "NO") << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_QualityVsQuantity.txt", "r", stdin);
    freopen("../data/output_QualityVsQuantity.txt", "w", stdout);
    freopen("../data/error_QualityVsQuantity.txt", "w", stderr);
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