/**
 B. Avoid Local Maximums
time limit per test2 seconds
memory limit per test256 megabytes
inputstandard input
outputstandard output
You are given an array 𝑎 of size 𝑛. Each element in this array is an integer between 1 and 109.

You can perform several operations to this array. During an operation, you can replace an element in the array with any integer between 1 and 109.

Output the minimum number of operations needed such that the resulting array doesn't contain any local maximums, and the resulting array after the operations.

An element 𝑎𝑖 is a local maximum if it is strictly larger than both of its neighbors (that is, 𝑎𝑖>𝑎𝑖−1 and 𝑎𝑖>𝑎𝑖+1). Since 𝑎1 and 𝑎𝑛 have only one neighbor each, they will never be a local maximum.

Input
Each test contains multiple test cases. The first line will contain a single integer 𝑡 (1≤𝑡≤10000) — the number of test cases. Then 𝑡 test cases follow.

The first line of each test case contains a single integer 𝑛 (2≤𝑛≤2⋅105) — the size of the array 𝑎.

The second line of each test case contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (1≤𝑎𝑖≤109), the elements of array.

It is guaranteed that the sum of 𝑛 over all test cases does not exceed 2⋅105.

Output
For each test case, first output a line containing a single integer 𝑚 — minimum number of operations required. Then ouput a line consist of 𝑛 integers — the resulting array after the operations. Note that this array should differ in exactly 𝑚 elements from the initial array.

If there are multiple answers, print any.
5
3
2 1 2
4
1 2 3 1
5
1 2 1 2 1
9
1 2 1 3 2 3 1 2 1
9
2 1 3 1 3 1 3 1 3

 */
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