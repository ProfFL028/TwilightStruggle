

#include <iostream>

using namespace std;


void solve() {
    int n;
    cin >> n;
    int answer = 1;
    for (int i = 0; i < n; i++) {
        answer *= 2;
    }
    cout << answer - 1 << endl;

}

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {

        solve();

        testCase--;
    }
}