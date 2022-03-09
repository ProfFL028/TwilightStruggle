#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

bool sortBySec(const tuple<ll, ll> &a, const tuple<ll, ll> &b) {
    return get<1>(a) < get<1>(b);
}

ll minVector(vector<ll> vec) {
    ll m = LLONG_MAX;
    for (auto v: vec) {
        m = min(v, m);
    }
    return m;
}

ll findMin(ll examCount, vector<ll> examDays, ll remains) {
    int max = examDays[0];
    int maxIdx = 0;
    for (int i = 1; i < examCount - 1; i++) {
        if (examDays[i] - examDays[i - 1] > max) {
            max = examDays[i] - examDays[i - 1];
            maxIdx = i;
        }
    }
    if ((max - 1) / 2 > remains) {
        examDays.erase(examDays.begin() + maxIdx);
        examDays.push_back((max - 1) / 2);
    }
    return minVector(examDays);
}

void solve() {
    ll examCount, days;
    cin >> examCount >> days;

    vector<ll> examDays(examCount);
    cin >> examDays[0];
    ll minIndex = 0;
    ll min = examDays[0] - 1;

    for (int i = 1; i < examCount; i++) {
        cin >> examDays[i];
        ll rest = examDays[i] - examDays[i - 1] - 1;
        if (rest < min) {
            minIndex = i;
            min = rest;
        }
    }
    ll remains = days - examDays[examCount - 1];
    if (minIndex == 0) {
        examDays.erase(examDays.begin());
        ll minValue = findMin(examCount, examDays, remains);
        cout << minValue << endl;
    } else if (minIndex == examCount - 1) {
        examDays[examCount - 1] = days - 1;
        cout << minVector(examDays) << endl;
    } else {
        // 移动 i
        vector<ll> bak;
        for (auto v: examDays) {
            bak.push_back(v);
        }
        examDays.erase(examDays.begin() + minIndex);
        ll minValue1 = findMin(examCount, examDays, remains);

        bak.erase(examDays.begin() + minIndex - 1);
        ll minValue2 = findMin(examCount, bak, remains);
        cout << max(minValue1, minValue2) << endl;
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