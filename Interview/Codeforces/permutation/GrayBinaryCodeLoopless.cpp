#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 6;
    vector<int> arr(n + 1, 0);
    vector<int> f(n + 1, 0);
    std::iota(f.begin(), f.end(), 0);

    int j = f[0];
    while (j != n) {
        for (int i = n-1; i >=0; i--) {
            cout << arr[i];
        }
        cout << endl;
        j = f[0];
        f[0] = 0;

        f[j] = f[j + 1];
        f[j + 1] = j + 1;
        arr[j] = 1 - arr[j];
    }

    return 0;
}