#include <iostream>

#include "BigInteger.h"
int main() {
    BigInteger b1("12345", 5);
    BigInteger b2("12345", 5);
    BigInteger* b3 = b1.add(b2);

    b3->print();

    return 0;
}
