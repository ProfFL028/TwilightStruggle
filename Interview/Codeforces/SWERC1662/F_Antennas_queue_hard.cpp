#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define D(v) for (int x : v) cerr << x << ' '; cerr << endl;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--){
        int n, a, b;
        cin >> n >> a >> b;
        vector<int> v(n+1);
        int m = round(sqrt(n));
        vector<set<int>> vs(m+2, {int(1e9)});
        for (int i = 1; i <= n; i++){
            cin >> v[i];
            if (i != a)
                vs[v[i]/m].insert(i);
        }
        bool done = false;
        queue<pair<int, int>> Q;
        Q.push({a, 0});
        if (a == b){
            cout << "0\n";
            done = true;
        }
        while (!Q.empty() and !done){
            int x = Q.front().first;
            int d = Q.front().second;
            Q.pop();
            for (int i = 0; i <= m+1 and !done; i++){
                int l = x - min(i*m+m-1, v[x]);
                int r = 2*x-l;
                auto it = vs[i].lower_bound(l);
                vector<int> S;
                while (*it <= r){
                    if (v[*it] >= abs(*it - x)){
                        S.push_back(*it);
                    }
                    it++;
                }
                for (int y : S){
                    vs[i].erase(y);
                    Q.push({y, d+1});
                    if (y == b){
                        done = true;
                        cout << d+1 << '\n';
                    }
                }
            }
        }

    }
}