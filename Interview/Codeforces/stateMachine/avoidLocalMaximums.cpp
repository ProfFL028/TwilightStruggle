//
// Created by ProfFL on 2022/2/22.
//
#include <iostream>
using namespace std;

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        int n;
        cin >> n;
        int* arr = new int[n];
        int prePreStatus = 0;
        int preStatus = 0;
        int changeCount = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (i > 0) {
                if (arr[i] > arr[i - 1]) {
                    if (preStatus == -1 && prePreStatus == 1) {
                        changeCount++;
                        arr[i - 1] = arr[i - 2] > arr[i] ? arr[i - 2] : arr[i];
                        preStatus = 0;
                        prePreStatus = 0;
                    } else {
                        preStatus = 1;
                    }
                } else {
                    if (preStatus == -1 && prePreStatus == 1) {
                        changeCount++;
                        arr[i - 1] = arr[i - 2];
                        prePreStatus = 0;
                    } else {
                        prePreStatus = preStatus;
                    }
                    preStatus = arr[i] == arr[i - 1] ? 0 : -1;
                }
            }
        }
        if (preStatus == -1 && prePreStatus == 1) {
            changeCount++;
            arr[n - 1] = arr[n - 2];
        }
        cout << changeCount << endl;
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        delete [] arr;
        testCase--;
    }
    return 0;
}