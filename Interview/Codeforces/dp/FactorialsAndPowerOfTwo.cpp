/**
 * https://codeforces.com/contest/1646/problem/C
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

ll *powerfulNums = new ll[]{1, 2, 4, 6, 8, 16, 24, 32, 64, 120, 128, 256, 512, 720, 1024, 2048, 4096, 5040,
                            8192, 16384, 32768, 40320, 65536, 131072, 262144, 362880, 524288, 1048576,
                            2097152, 3628800, 4194304, 8388608, 16777216, 33554432, 39916800, 67108864,
                            134217728, 268435456, 479001600, 536870912, 1073741824, 2147483648, 4294967296,
                            6227020800, 8589934592, 17179869184, 34359738368, 68719476736, 87178291200};

int binarySearch(ll num, int count) {
    if (num < 0) {
        return -1;
    }
    for (int i = 0; i < 49; i++) {
        if (num == powerfulNums[i]) {
            return count + 1;
        }
    }
    int half = num / 2;
    int minCount = -1;
    int j = 0;
    while (j < 49) {
        if (powerfulNums[j] > half) {
            int newCount = binarySearch(num - powerfulNums[j], count+1);
            if (newCount != -1) {
                if (minCount == -1) {
                    minCount = newCount;
                } else {
                    minCount = min(minCount, newCount);
                }
            }
        }
        if (powerfulNums[j] > num) {
            break;
        }
        j++;
    }
    return minCount;
}

void solve() {
    ll n;
    cin >> n;
    int result = binarySearch(n, 0);
    cout << result << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_FactorialsAndPowerOfTwo.txt", "r", stdin);
    freopen("../data/output_FactorialsAndPowerOfTwo.txt", "w", stdout);
    freopen("../data/error_FactorialsAndPowerOfTwo.txt", "w", stderr);
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