// codeforces:

#include <bits/stdc++.h>

using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<int> a, b;
    int x;
    for (int i = 0; i < (1ll << n); i++) {
        a.push_back(i+1);
    }
    int tmp[4];
    while (a.size() > 2) {
        while (a.size() > 0) {
            for (int i = 0; i < 4; i++) {
                tmp[i] = a.back();
                a.pop_back();
            }
            cout << "? " << tmp[0] << " " << tmp[2] << endl;
            cin >> x;
            if (x == 1) {
                cout << "? " << tmp[0] << " " << tmp[3] << endl;
                cin >> x;
                if (x == 1) {
                    b.push_back(tmp[0]);
                } else {
                    b.push_back(tmp[3]);
                }
            } else if (x == 2) {
                cout << "? " << tmp[1] << ' ' << tmp[2] << endl;
                cin >> x;
                if (x == 1) b.push_back(tmp[1]);
                else b.push_back(tmp[2]);
            } else {
                cout << "? " << tmp[1] << ' ' << tmp[3] << endl;
                cin >> x;
                if (x == 1) b.push_back(tmp[1]);
                else b.push_back(tmp[3]);
            }
        }
        a = b;
        b.clear();
    }
    if (a.size() == 2) {
        cout << "? " << a[0] << ' ' << a[1] << endl;
        cin >> x;
        if (x == 2) a[0] = a[1];
    }
    cout << "! " << a[0] << endl;
}

int main() {

    int testCase = 1;
    cin >> testCase;
    while (testCase > 0) {
        solve();
        testCase--;
    }
    return 0;
}