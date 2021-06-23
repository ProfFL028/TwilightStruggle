//
// Created by Administrator on 2021/6/23.
//
#include <iostream>
#include <bitset>
#include "../leetcode/Number1CounterInInteger.cpp"

int main() {
    uint32_t n = 56;

    std::cout << (n<<1) <<std::endl;
    std::bitset<32> x(-n);
    std::bitset<32> nn(n);
    std::cout << nn << std::endl;
    std::cout << x << std::endl;
    std::cout << Number1CounterInInteger::hammingWeight(n) << std::endl;
    std::cout << Number1CounterInInteger::hammingWeight2(n) << std::endl;

    return 0;
};