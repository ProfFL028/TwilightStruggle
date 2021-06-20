//
// Created by Administrator on 2021/6/20.
//
#include "Vector.cpp"

/**
 * add two big integer which are represented in char*
 * @param a left integer
 * @param b right integer
 * @return  result of a+b, also represented in char*
 */
char* BigIntegerAdd(char* a, char* b) {
    int lengthA = strlen(a);
    int lengthB = strlen(b);

    Vector<char> result;

    int extra = 0;
    for (int i = 0; i < lengthB; i++) {
        int value = a[lengthA - i - 1] - '0' + b[lengthB - i - 1] - '0' + extra;
        result.add((value % 10) + '0');
        extra = value / 10;
    }
    int lengthDiff = lengthA - lengthB;
    for (int i = 0; i < lengthDiff; i++) {
        int value = a[lengthDiff - i - 1] - '0' + extra;
        result.add((value % 10) + '0');
        extra = value / 10;
    }
    if (extra > 0)
        result.add(extra + '0');

    char* resultStr = new char[10];
return resultStr;
}
