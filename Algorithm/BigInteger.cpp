//
// Created by Administrator on 2021/6/17.
//

#include "BigInteger.h"
#include "string.h"
#include <iostream>

BigInteger::BigInteger() {
    memset(this->value, 0, sizeof(this->value));
}

BigInteger::BigInteger(char *v, int l) {
    this->length = l;
    memcpy(this->value, v, sizeof(int) * l);
}

BigInteger *BigInteger::add(BigInteger anotherBigInteger) {
    BigInteger *result = new BigInteger();
    int extra = 0;
    for (int i = 0; i < this->length; i++) {
        int intValue1 = this->value[i] - '0';
        std::cout << intValue1 << std::endl;
        for (int j = 0; j < this->length; j++) {
            int intValue2 = anotherBigInteger.value[j] - '0';
            int curValue = intValue1 * intValue2 + result->value[i + j] + extra;
            result->value[i + j] = curValue % 10;
            extra = curValue / 10;
        }
        extra = 0;
    }

    return result;
}

void BigInteger::print() {
    std::cout << this->value << std::endl;
}
