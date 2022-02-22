/**
 * A. Min Or Sum
time limit per test1 second
memory limit per test256 megabytes
inputstandard input
outputstandard output
You are given an array 𝑎 of size 𝑛.

You can perform the following operation on the array:

Choose two different integers 𝑖,𝑗 (1≤𝑖<𝑗≤𝑛), replace 𝑎𝑖 with 𝑥 and 𝑎𝑗 with 𝑦. In order not to break the array, 𝑎𝑖|𝑎𝑗=𝑥|𝑦 must be held, where | denotes the bitwise OR operation. Notice that 𝑥 and 𝑦 are non-negative integers.
Please output the minimum sum of the array you can get after using the operation above any number of times.

Input
Each test contains multiple test cases. The first line contains the number of test cases 𝑡 (1≤𝑡≤1000). Description of the test cases follows.

The first line of each test case contains an integer 𝑛 (2≤𝑛≤100) — the size of array 𝑎.

The second line of each test case contains 𝑛 integers 𝑎1,𝑎2,…,𝑎𝑛 (0≤𝑎𝑖<230).

Output
For each test case, print one number in a line — the minimum possible sum of the array.

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