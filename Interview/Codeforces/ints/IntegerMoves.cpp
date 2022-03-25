#include <iostream>
#include <math.h>
using namespace std;

void solve() {
    int x, y;
    cin >> x >> y;
    int sum = x* x + y * y;
    int steps = 0;
    if (sum == 0) {
        cout << "0" << endl;
    }
    while (sum > 0) {
        int sqrted = sqrt(sum);
        sum = sum - sqrted * sqrted;
        steps++;
    }
    cout << steps << endl;
}

int main() {
    int testCase = 1;
    cin >> testCase;
    while (testCase > 0) {
        solve();
        testCase--;
    }
}