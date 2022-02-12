#include <iostream>

using namespace std;
/**
 * You are given a string s of length n and a number k. Let's denote by rev(s) the reversed string s (i.e. rev(s)=snsn−1...s1). You can apply one of the two kinds of operations to the string:

replace the string s with s+rev(s)
replace the string s with rev(s)+s
How many different strings can you get as a result of performing exactly k operations (possibly of different kinds) on the original string s?

In this statement we denoted the concatenation of strings s and t as s+t. In other words, s+t=s1s2...snt1t2...tm, where n and m are the lengths of strings s and t respectively.

Input
The first line contains one integer t (1≤t≤100) — number of test cases. Next 2⋅t lines contain t test cases:

The first line of a test case contains two integers n and k (1≤n≤100, 0≤k≤1000) — the length of the string and the number of operations respectively.

The second string of a test case contains one string s of length n consisting of lowercase Latin letters.

Output
For each test case, print the answer (that is, the number of different strings that you can get after exactly k operations) on a separate line.

It can be shown that the answer does not exceed 109 under the given constraints.
 * @level 1
 */

int main() {
    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        int strLen, opCount = 0;
        cin >> strLen >> opCount;
        const int MAX_BUFFER = 1024;
        unsigned char *str = new unsigned char[MAX_BUFFER];
        cin >> str;

        if (opCount > 0) {
            bool isRecursive = true;
            for (int i = 0; i < strLen / 2; i++) {
                isRecursive = str[i] == str[strLen - i - 1];
                if (!isRecursive) {
                    break;
                }
            }
            cout << (isRecursive ? 1 : 2) << endl;
        } else {
            cout << 1 << endl;
        }
        delete [] str;
        testCase--;
    }

    return 0;
}