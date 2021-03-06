/**
 B. Avoid Local Maximums
time limit per test2 seconds
memory limit per test256 megabytes
inputstandard input
outputstandard output
You are given an array ๐ of size ๐. Each element in this array is an integer between 1 and 109.

You can perform several operations to this array. During an operation, you can replace an element in the array with any integer between 1 and 109.

Output the minimum number of operations needed such that the resulting array doesn't contain any local maximums, and the resulting array after the operations.

An element ๐๐ is a local maximum if it is strictly larger than both of its neighbors (that is, ๐๐>๐๐โ1 and ๐๐>๐๐+1). Since ๐1 and ๐๐ have only one neighbor each, they will never be a local maximum.

Input
Each test contains multiple test cases. The first line will contain a single integer ๐ก (1โค๐กโค10000) โ the number of test cases. Then ๐ก test cases follow.

The first line of each test case contains a single integer ๐ (2โค๐โค2โ105) โ the size of the array ๐.

The second line of each test case contains ๐ integers ๐1,๐2,โฆ,๐๐ (1โค๐๐โค109), the elements of array.

It is guaranteed that the sum of ๐ over all test cases does not exceed 2โ105.

Output
For each test case, first output a line containing a single integer ๐ โ minimum number of operations required. Then ouput a line consist of ๐ integers โ the resulting array after the operations. Note that this array should differ in exactly ๐ elements from the initial array.

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