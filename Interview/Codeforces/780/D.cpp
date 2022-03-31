// codeforces: 

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int LEN = 2 * 10e5 + 5;
int arr[LEN];

tuple<int, int, int> maxSub(int start, int end) {
    int twoCount =0;
    int negCount = 0;
    for (int i = start; i <= end; i++) {
        if (abs(arr[i]) == 2) {
            twoCount++;
        }
        if (arr[i] < 0) {
            negCount++;
        }
    }
    if (negCount % 2 == 0) {
        return tuple<int, int, int>(twoCount, start, end);
    } else {
        int left2Count = 0;
        int leftIdx = 0;
        for (int i = start; i <= end; i++) {
            if (abs(arr[i]) == 2) {
                left2Count++;
            }
            if (arr[i] < 0) {
                leftIdx = i+1;
                break;
            }
        }

        int right2Count = 0;
        int rightIdx = 0;
        for (int i = end; i>=start; i--) {
            if (abs(arr[i]) == 2) {
                right2Count++;
            }
            if (arr[i] < 0) {
                rightIdx = i-1;
                break;
            }
        }
        if (left2Count > right2Count) {
            return tuple<int, int, int>(twoCount - right2Count, start, rightIdx);
        } else {
            return tuple<int, int, int>(twoCount - left2Count, leftIdx, end);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> zeroPos;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int k = 0;
    while (k < n) {
        while (k < n && arr[k] == 0) {
            k++;
        }
        if (k == n) {
            break;
        }
        zeroPos.push_back(k);
        while (k < n && arr[k] != 0) {
            k++;
        }
        zeroPos.push_back(k - 1);
    }
    int ans = 0;
    int x = 0;
    int y = 0;
    for (int i = 0; i < zeroPos.size() - 1; i++) {
        auto tt = maxSub(zeroPos[i], zeroPos[i + 1]);
        if (ans < get<0>(tt)) {
            ans = get<0>(tt);
            x = get<1>(tt);
            y = get<2>(tt);
        }
    }
    if (ans >= 1) {
        cout << x << " " << (n - 1 - y) << endl;
    } else {
        cout << n << " " << 0 << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
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