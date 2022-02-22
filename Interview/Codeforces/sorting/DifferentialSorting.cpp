
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        int n;
        cin >> n;
        double *arr = new double[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        vector<tuple<int, int, int> > operators;
        double maxValue = arr[n - 1];
        if (maxValue <= 0) {
            bool isSolvable = true;
            for (int i = 1; i < n; i++) {
                if (arr[i] < arr[i-1]) {
                    isSolvable = false;
                    break;
                }
            }
            if (isSolvable) {
                cout << 0 << endl;
            } else {
                cout << -1 << endl;
            }
        } else {
            double minValue = arr[n - 2];
            if (minValue <= maxValue) {
                cout << n-2 << endl;
                for (int i = 1; i < n-1; i++) {
                    cout << i << " " << (n - 2) << " " << (n - 1) << endl;
                }
            } else {
                cout << -1 << endl;
            }
        }

        delete[] arr;
        testCase--;
    }
    return 0;
}