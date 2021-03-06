/**
 * A. Min Or Sum
time limit per test1 second
memory limit per test256 megabytes
inputstandard input
outputstandard output
You are given an array ๐ of size ๐.

You can perform the following operation on the array:

Choose two different integers ๐,๐ (1โค๐<๐โค๐), replace ๐๐ with ๐ฅ and ๐๐ with ๐ฆ. In order not to break the array, ๐๐|๐๐=๐ฅ|๐ฆ must be held, where | denotes the bitwise OR operation. Notice that ๐ฅ and ๐ฆ are non-negative integers.
Please output the minimum sum of the array you can get after using the operation above any number of times.

Input
Each test contains multiple test cases. The first line contains the number of test cases ๐ก (1โค๐กโค1000). Description of the test cases follows.

The first line of each test case contains an integer ๐ (2โค๐โค100) โ the size of array ๐.

The second line of each test case contains ๐ integers ๐1,๐2,โฆ,๐๐ (0โค๐๐<230).

Output
For each test case, print one number in a line โ the minimum possible sum of the array.

4
3
1 3 2
5
1 2 4 8 16
2
6 6
3
3 5 6

 *
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