#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

struct Classroom {
    ll id;
    ll time;
    ll progress;
};

struct PathNode {
    ll cur;
    ll pre;
};
vector<ll> lessonPaths;
vector<ll> timeElapsed;

ll dpSearch(const vector<Classroom> &classroom) {
    ll answer = LLONG_MAX;

    ll dp[201];
    dp[0] = 0;
    for (int i = 1; i < 200; ++i) {
        dp[i] = LLONG_MAX;
    }

    PathNode learningPath[201];
    learningPath[0] = PathNode{0, -1};

    for (ll i = 0; i < classroom.size(); ++i) {
        for (ll j = 100; j >= 0; --j) {
            if (dp[j] != LLONG_MAX) {
                dp[j + classroom[i].progress] = min(dp[j + classroom[i].progress], dp[j] + classroom[i].time);
                learningPath[j + classroom[i].progress] = PathNode{i, learningPath[j].cur};
            }
        }
    }

    ll learningIdx = -1;
    for (ll j = 100; j < 200; ++j) {
        if (answer > dp[j]) {
            learningIdx = j;
            answer = dp[j];
        }
    }
    if (learningIdx > 0) {
        while (learningPath[learningIdx].pre != -1) {
            lessonPaths.push_back(classroom[learningPath[learningIdx].cur].id);
            learningIdx -= classroom[learningPath[learningIdx].cur].progress;
        }
    }

    return answer;
}

void solve() {
    ll lessonCount, classCount;
    cin >> lessonCount >> classCount;
    vector<ll> lessonTimes(lessonCount);
    for (ll i = 0; i < lessonCount; ++i) {
        cin >> lessonTimes[i];
    }
    vector<vector<Classroom>> classes(lessonCount);
    for (ll i = 0; i < classCount; ++i) {
        Classroom classroom{};
        ll id;
        cin >> id;
        classroom.id = i + 1;
        cin >> classroom.time >> classroom.progress;
        classes[id-1].push_back(classroom);
    }

    ll totalTime = 0;
    for (ll i = 0; i < lessonCount; ++i) {
        totalTime += dpSearch(classes[i]);
        if (totalTime > lessonTimes[i]) {
            cout << "-1" << endl;
            return;
        }
    }
    cout << lessonPaths.size() << endl;
    for (auto v: lessonPaths) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_AUA.txt", "r", stdin);
    freopen("../data/output_AUA.txt", "w", stdout);
    freopen("../data/error_AUA.txt", "w", stderr);
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