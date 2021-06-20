//
// Created by Administrator on 2021/6/20.
//
#include "../dataStructure/Vector.h"

int main() {
    Vector<char> v;
    for (int i = 0; i < 10; i++) {
        v.add(i + '0');
    }
    v.print();
}
