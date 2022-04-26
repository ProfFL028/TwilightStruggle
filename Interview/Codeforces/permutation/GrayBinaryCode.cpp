#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 5;
    vector<vector<string>> t(n + 1, vector<string>());
    t[1].push_back("0");
    t[1].push_back("1");

    // method 1: T0=null, T_(n+1) = 0T_n, 1T^R_n
    for (int i = 2; i <= 5; i++) {
        for (auto &s: t[i - 1]) {
            t[i].push_back("0" + s);
        }
        int sz = t[i - 1].size();
        for (int j = sz - 1; j >= 0; j--) {
            t[i].push_back("1" + t[i - 1][j]);
        }
    }

    for (auto &x: t[5]) {
        cout << x << endl;
    }

    cout << "another simple method" << endl;

    // g(k) = k xor k/2
    for (int i = 0; i < (2 << n); i++) {
        int k = i xor (i / 2);
        cout << bitset<8>(k) << endl;
    }

    cout << "simple computation" << endl;
    vector<int> arr(n + 1, 0);
    arr[n] = 1;
    while (true) {
        for (int i = n - 1; i >= 0; i--) {
            cout << arr[i];
        }
        cout << endl;
        arr[n] = 1 - arr[n];
        int j;
        if (arr[n] == 0) {
            j = 0;
        } else {
            j = 1;
            while (!arr[j - 1]) j++;
        }
        if (j == n) break;
        arr[j] = 1 - arr[j];
    }

    return 0;
}

