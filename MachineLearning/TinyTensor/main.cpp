#include <iostream>
#include "core/Operators.h"


int main() {
    double v = Add::calc(Mul::calc(5, 6), 3);
    std::cout << v  << std::endl;

    return 0;
}
