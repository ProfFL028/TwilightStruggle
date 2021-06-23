//
// Created by Administrator on 2021/6/23.
//
#include <iostream>
#include <bitset>
#include "../leetcode/Number1CounterInInteger.cpp"

int main() {
    uint32_t n = 0b01111111111111111111111111111111;

    std::cout << (n<<1) <<std::endl;
    std::bitset<32> x(-n);
    std::bitset<32> nn(n);
    std::cout << nn << std::endl;
    std::cout << x << std::endl;
    std::cout << Number1CounterInInteger::hammingWeight(n) << std::endl;
    std::cout << Number1CounterInInteger::hammingWeight2(n) << std::endl;

    std::bitset<32> k (n & -n);
    std::cout << k << std::endl;

    std::bitset<32> s (n - (n & -n));
    std::cout << s << std::endl;

    std::bitset<32> m ( ((n >> 16) & 0b00000000000000001111111111111111)
                       + (n & 0b00000000000000001111111111111111));
    std::cout << m << std::endl;

    return 0;
};