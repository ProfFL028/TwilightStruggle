//
// Created by Administrator on 2021/6/17.
//

#ifndef ALGORITHM_BIGINTEGER_H
#define ALGORITHM_BIGINTEGER_H


class BigInteger {

public:
    static const int MAX_LENGTH = 10000;

private:
    char* value;
    int length;
public:
    BigInteger();

    BigInteger(char *v, int length);

    BigInteger* add(BigInteger anotherBigInteger);

    void print();
};


#endif //ALGORITHM_BIGINTEGER_H
