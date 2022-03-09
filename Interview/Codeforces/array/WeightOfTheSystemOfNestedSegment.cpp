#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

bool sortByThird(const tuple<ll, ll, ll> &a, const tuple<ll, ll, ll> &b) {
    return get<2>(a) < get<2>(b);
}
bool sortBySec(const tuple<ll, ll, ll> &a, const tuple<ll, ll, ll> &b) {
    return get<1>(a) < get<1>(b);
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<tuple<ll, ll, ll>> minValues;
    for (int i = 0; i < m; i++) {
        tuple<ll, ll, ll> value;
        get<0>(value) = i+1;
        cin >> get<1>(value) >> get<2>(value);
        minValues.push_back(value);
    }
    sort(minValues.begin(), minValues.end(), sortByThird);
    minValues.resize(2 * n);
    ll minValue = 0;
    for (auto v : minValues) {
        minValue += get<2>(v);
    }
    cout << minValue << endl;
    sort(minValues.begin(), minValues.end(), sortBySec);
    for (int i = 0; i < n; i++) {
        cout << get<0>(minValues[i]) << " " << get<0>(minValues[2 * n - i - 1]) << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_WNS.txt", "r", stdin);
    freopen("../data/output_WNS.txt", "w", stdout);
    freopen("../data/error_WNS.txt", "w", stderr);
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