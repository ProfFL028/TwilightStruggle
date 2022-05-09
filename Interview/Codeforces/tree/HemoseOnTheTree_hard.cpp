// codeforces: https://codeforces.com/contest/1670/problem/E

/**
 * Let's look at the minimum maximum value that we can get if we have an array of numbers from [1,2(𝑝+1)−1] and we are trying to get any prefix xor, the answer will be 2𝑝 because you can stop at the first integer that will have the bit 𝑝 so the answer will be ≥2𝑝.
We can apply the same concept here, for any arrangement we can start at the root and stop at the first node/edge that has the bit 𝑝 on. Let's try to find a construction that will make our answer always 2𝑝. This is one of the valid ways.
Select an arbitrary root.
Put 2𝑝 at the root.
Create 2𝑝−1 pairs from the remaining numbers of the form (𝑥,𝑥+2𝑝) where 𝑥<2𝑝
For every node we will do the following:
If its parent has the bit 𝑝 in its value the node will take the value 𝑥 and the edge to the parent will take 𝑥+2𝑝.
If its parent doesn't have the bit 𝑝 in its value the node will take the value 𝑥+2𝑝 and the edge to the parent will take 𝑥.
Using this construction you will find that the xor value form the root will alternate between 0 and 2𝑝 and 𝑥 which is always ≤2𝑝 .
 */
#include <bits/stdc++.h>

using namespace std;

//gcc optimization
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const int MOD = 1e9 + 7;

#define print(v) cout << v.size() << endl; for (auto& v: result) cout << v << " "; cout << endl;

const int MAX_N = 300000+5;

void solve() {
    int n;
    cin >> n;
    int N = 1 << n;

    vector<vector<pair<int, int>>> vex(N);
    vector<int> nodes(N, 0);
    vector<int> edges(N, 0);
    int c = 0;

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        vex[a].push_back(make_pair(b, i));
        vex[b].push_back(make_pair(a, i));
    }

    nodes[0] = N;
    function<void(int, int)> dfs = [&](int u, int v) {
        for (auto x : vex[u]) {
            if (x.first == v) continue;
            c++;
            edges[x.second] = c + ((nodes[u] & N) != 0 ? N : 0);
            nodes[x.first] = c + ((nodes[u] & N) != 0 ? 0 : N);
            dfs(x.first, u);
        }
    };

    dfs(0, -1);

    cout << 1 << endl;
    for (int i = 0; i < N; i++) {
        cout << nodes[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < N - 1; i++) {
        cout << edges[i] << " ";
    }
    cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
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