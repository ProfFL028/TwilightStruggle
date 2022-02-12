

#include <iostream>

using namespace std;

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        int n, k = 0;
        cin >> n >> k;

        if (k == 1) {
            cout << "YES" << endl;
            for (int i = 1; i <= n; i++) {
                cout << i << endl;
            }
        } else {
            if (n % 2 == 0) {
                cout << "YES" << endl;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < k; j++) {
                        cout << (i + j * n + 1) << " ";
                    }
                    cout << endl;
                }
            } else {
                cout << "NO" << endl;
            }
        }

        testCase--;
    }
}