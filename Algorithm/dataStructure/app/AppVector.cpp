
#include "Vector.h"
#include <iostream>

int main() {
    ds::Vector<int> ints;
    ints.insert(5);
    ints.insert(10);
    ints.insert(100);

    std::cout << "after insert 5, 10, 100" << std::endl;
    std::cout << ints << std::endl;

    ds::Vector<int>* copy = &ints;
    std::cout << "smooth reference version: ";
    std::cout << *copy << std::endl;

    ds::Vector<int> copy2 = ints;
    std::cout << "copy from ints: ";
    std::cout << copy2 << std::endl;


    int first = ints.pop();
    std::cout << "after remove " << first << std::endl;
    std::cout << ints << std::endl;

    std::cout << "smooth copy version: ";
    std::cout << *copy << std::endl;

    std::cout << "deep copy version:" << copy2 << std::endl;

    return 0;
}