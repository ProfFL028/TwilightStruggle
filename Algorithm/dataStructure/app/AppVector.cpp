
#include "Vector.h"
#include <iostream>

int main() {
    ds::Vector<int> ints;
    ints.add(5);
    ints.add(10);
    ints.add(100);

    std::cout << "after insert 5, 10, 100" << std::endl;
    std::cout << ints << std::endl;
    return 0;
}