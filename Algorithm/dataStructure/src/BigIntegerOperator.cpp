//
// Created by Administrator on 2021/6/20.
//
#include "Vector.cpp"

/**
 * Add two big integer which are represented in char*.
 * algorithm explain: Add char represented integer value at each index plus carry(extra) from last to first.
 * @param a left integer
 * @param b right integer
 * @return  result of a+b, also represented in char*
 */
char* bigIntegerAdd(char* a, char* b) {
    int lengthA = strlen(a);
    int lengthB = strlen(b);

    // if b is longer than a, then swap a and b.
    if (lengthB > lengthA) {
        return bigIntegerAdd(b, a);
    }
    Vector<char> result;

    int extra = 0; // carry
    // add from last element to shorter array's first element.
    for (int i = 0; i < lengthB; i++) {
        // convert char to integer 0 and plus each element.
        int value = a[lengthA - i - 1] - '0' + b[lengthB - i - 1] - '0' + extra;
        // store result to char format
        result.add((value % 10) + '0');
        // carry
        extra = value / 10;
    }
    int lengthDiff = lengthA - lengthB;
    // add left element.
    for (int i = 0; i < lengthDiff; i++) {
        int value = a[lengthDiff - i - 1] - '0' + extra;
        result.add((value % 10) + '0');
        extra = value / 10;
    }
    // if carry is greater than 0, then add extra to result.
    if (extra > 0)
        result.add(extra + '0');

    // convert result to char*
    // "// TODO: implement this."
    return a;
}
