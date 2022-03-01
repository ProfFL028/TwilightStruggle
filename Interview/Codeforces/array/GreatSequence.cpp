#include<iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;


void solve() {
    int len = 1;
    cin >> len;
    ll arr[len];
    ll x = 1;
    cin >> x;
    ll c = 0;
    map<ll, int> notFound;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
        if (arr[i] % x == 0) {
            int t = arr[i] / x;
            if (notFound.find(t) != notFound.end() && notFound[t] > 0) {
                notFound[t] -= 1;
                c--;
                continue;
            }
        }
        if (arr[i] * x <= 10e9l) {
            ll t = arr[i] * x;
            if (notFound.find(t) != notFound.end() && notFound[t] > 0) {
                notFound[t] -= 1;
                c--;
                continue;
            }
        }
        if (notFound.find(arr[i]) != notFound.end() && notFound[arr[i]] > 0) {
            notFound[arr[i]] += 1l;
        } else {
            notFound[arr[i]] = 1l;
        }
        c++;
    }
    cout << c << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_GreatSequence.txt", "r", stdin);
    freopen("../data/output_GreatSequence.txt", "w", stdout);
    freopen("../data/error_GreatSequence.txt", "w", stderr);
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