//
// Created by ProfFL on 2022/2/22.
//

/**
 *
4
3
1 3 2
5
1 2 4 8 16
2
6 6
3
3 5 6
 */
#include <iostream>
#include <bitset>
using namespace std;

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        int n = 0;
        cin >> n;
        int* arr = new int[n];
        bitset<32> result(0);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            result |= bitset<32>(arr[i]);
        }
        cout << int(result.to_ullong()) << endl;
        delete [] arr;
        testCase--;
    }
    return 0;
}