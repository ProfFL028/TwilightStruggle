//
// Created by Administrator on 2021/6/20.
//
#include "../dataStructure/Vector.cpp"

int main() {
    Vector<char> v;
    for (int i = 0; i < 10; i++) {
        v.add(i + '0');
    }
    // it will print 9876543210
    v.print();

    v.remove();
    // it will print 876543210
    v.print();


    return 0;
}
