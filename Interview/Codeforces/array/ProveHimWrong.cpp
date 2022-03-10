

#include <iostream>

using namespace std;


void solve() {
    int n;
    cin >> n;
    if (n > 19) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        int k = 1;
        for (int i = 0; i < n; i++) {
            cout << k << " ";
            k *=3;
        }
        cout << endl;
    }

}

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {

        solve();

        testCase--;
    }
}