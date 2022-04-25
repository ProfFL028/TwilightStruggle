#include <bits/stdc++.h>

using namespace std;

int main() {

    int m[7] = {9, 1, 3, 3, 2, 2, 2};
    int a[7] = {0, 0, 0, 0, 0, 0, 0};
    int ans = 0;
    int i = 5;
    while (i >= 0) {
        ans++;
        a[6]++;
        if (a[6] > m[6]) {
            a[6] = 0;
            i = 5;
            while (i >= 0 && a[i] == m[i]) {
                a[i] = 0;
                i--;
            };
            if (i >= 0) {
                a[i]++;
            }
        }
    }

    cout << ans << endl;
    int tmp = 1;
    for (int k = 0; k < 7; k++) {
        tmp *= (m[k] + 1);
    }
    cout << tmp << endl;

    return 0;
}