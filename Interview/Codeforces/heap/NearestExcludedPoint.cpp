#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;


map<int, int> mapPoints[2000005];
pair<int, int> points[2000005];
pair<int, int> answers[2000005];
int visited[2000005];

void solve() {
    int numCount;
    cin >> numCount;
    const pair<int, int> directions[4] = {pair<int, int>(-1, 0), pair<int, int>(0, -1), pair<int, int>(0, 1),
                                          pair<int, int>(1, 0)};
    for (int i = 0; i < numCount; i++) {
        ll a, b;
        cin >> a >> b;
        mapPoints[a][b]= i;
        points[i]= make_pair(a, b);
    }
    for (int i = 0; i < numCount; ++i) {
        answers[i] = make_pair(1e9,1e9);
        visited[i] = 0;
    }

    queue<int> solvedQueue;
    for (int i = 0; i < numCount; ++i) {
        for (const auto &direction: directions) {
            int nx = points[i].first + direction.first;
            int ny = points[i].second + direction.second;
            if (!mapPoints[nx].count(ny)) {
                solvedQueue.push(i);
                answers[i] = make_pair(nx, ny);
                visited[i] = 1;
                break;
            }
        }
    }

    while (!solvedQueue.empty()) {
        int p = solvedQueue.front();
        solvedQueue.pop();
        int x = points[p].first;
        int y = points[p].second;
        for (const auto &direction: directions) {
            int nx = x + direction.first;
            int ny = y + direction.second;

            if (mapPoints[nx].count(ny) && !visited[mapPoints[nx][ny]]) {

                solvedQueue.push(mapPoints[nx][ny]);
                answers[mapPoints[nx][ny]] = answers[p];
                visited[mapPoints[nx][ny]] = 1;
            }
        }
    }

    for (int i = 0;i < numCount; ++i) {
        tuple<int, int> answer = answers[i];
        cout << get<0>(answer) << " " << get<1>(answer) << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_NearestExcludedPoint.txt", "r", stdin);
    freopen("../data/output_NearestExcludedPoint.txt", "w", stdout);
    freopen("../data/error_NearestExcludedPoint.txt", "w", stderr);
#endif
    fast()

    int testCase = 1;
    // cin >> testCase;
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