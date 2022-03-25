// https://codeforces.com/contest/1657/problem/B
#include <iostream>
using namespace std;

void solve() {
    int n, B, x, y;
    cin >> n >> B >> x >> y;
    int sum = 0;
    int cur = 0;
    while(n > 1) {
        if ((cur + x) > B) {
            cur += x;
        } else {
            cur -= y;
        }
        sum += cur;
        --n;
    }
    cout << sum << endl;
}

int main() {
    int testCase;
    cin >> testCase;
    while (testCase > 0) {
        solve();
        --testCase;
    }
}