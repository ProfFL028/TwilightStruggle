
/**
 * Your friends Alice and Bob practice fortune telling.

Fortune telling is performed as follows. There is a well-known array a of n non-negative integers indexed from 1 to n. The tellee starts with some non-negative number d and performs one of the two operations for each i=1,2,…,n, in the increasing order of i. The possible operations are:

replace their current number d with d+ai
replace their current number d with d⊕ai (hereinafter ⊕ denotes the bitwise XOR operation)
Notice that the chosen operation may be different for different i and for different tellees.

One time, Alice decided to start with d=x and Bob started with d=x+3. Each of them performed fortune telling and got a particular number in the end. Notice that the friends chose operations independently of each other, that is, they could apply different operations for the same i.

You learnt that either Alice or Bob ended up with number y in the end, but you don't know whose of the two it was. Given the numbers Alice and Bob started with and y, find out who (Alice or Bob) could get the number y after performing the operations. It is guaranteed that on the jury tests, exactly one of your friends could have actually gotten that number.

Hacks

You cannot make hacks in this problem.

Input
On the first line of the input, you are given one number t (1≤t≤104) — the number of test cases. The following 2⋅t lines contain test cases.

The first line of each test case contains three numbers n, x, y (1≤n≤105, 0≤x≤109, 0≤y≤1015) — the length of array a, Alice's initial number (Bob's initial number is therefore x+3), and the number that one of the two friends got in the end.

The second line of each test case contains n numbers — the array a (0≤ai≤109).

It is guaranteed that the sum of n over all test cases does not exceed 105.

Output
For each test case, print the name of the friend who could get the number y: "Alice" or "Bob".

test case
4
1 7 9
2
2 0 2
1 3
4 0 1
1 2 3 4
2 1000000000 3000000000
1000000000 1000000000
 Alice
 Alice
 Bob
 Alice
 * @level 1
 */

#include <iostream>
#include <math.h>

using namespace std;

int main() {
    const char *alice = "Alice";
    const char *bob = "Bob";

    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        int arrSize;
        unsigned long long a, x = 0;
        cin >> arrSize;
        cin >> a >> x;
        long *arr = new long[arrSize];
        x = x % 2;
        int result = a % 4;
        for (int i = 0; i < arrSize; i++) {
            cin >> arr[i];
            result = (result + arr[i]) % 4;
        }
        result %= 2;
        if (result == x) {
            cout << alice << endl;
        } else {
            cout << bob << endl;
        }

        delete[] arr;
        testCase--;
    }

    return 0;
}