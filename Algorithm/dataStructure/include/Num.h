//
// Created by 方笠 on 2022/8/10.
//

#ifndef DATASTRUCTURE_NUM_H
#define DATASTRUCTURE_NUM_H

#include <iostream>
#include <vector>

template<class T>
T findMin() {
    T start{-1};
    T pre{0};
    while (start < pre) {
        pre = start;
        start *= 2;
    }
    return pre;
}

template<class T>
T findMax() {
    T start{1}, pre{0};
    while (start > pre) {
        pre = start;
        start *= 2;
    }
    return pre - 1 + pre;
}

void printPrimes(int N) {
    std::vector<int> a(N, 1);
    for (int i = 2; i < N; i++) {
        if (a[i]) {
            for (int j = i; i*j < N; j++) {
                a[i*j] = 0;
            }
        }
    }
    std::cout << "primary from 2-N are: ";
    for (int i = 2; i < N; i++) {
        if (a[i]) {
            std::cout << i << ",  ";
        }
    }
    std::cout <<"." << std::endl;
}

double randTest(int r, int N) {
    long long sum = 0;
    long long theta = 0;
    int i = 0;
    while (i < N) {
        int c = rand() % r;
        sum += c;
        theta += c * c;
        i++;
    }
    return (double) theta / N - ((double) sum / N) * ((double) sum / N) / N;
}

class Triangle {
public:
    std::pair<float, float> p1, p2, p3;
    static Triangle rand() {
        Triangle triangle;
        triangle.p1.first = (float)std::rand() / (float)RAND_MAX;
        triangle.p1.second = (float)std::rand() / (float)RAND_MAX;
        triangle.p2.first = (float)std::rand() / (float)RAND_MAX;
        triangle.p2.second = (float)std::rand() / (float)RAND_MAX;
        triangle.p3.first = (float)std::rand() / (float)RAND_MAX;
        triangle.p3.second = (float)std::rand() / (float)RAND_MAX;
        return triangle;
    }
public:
    float area() const {
        return abs(p1.first * (p2.second - p3.second) + p2.first * (p3.second - p1.second) + p3.first * (p1.second - p2.second));
    }
};

int coinFlipSimulation(int N) {
    int headCount = 0;
    for (int i = 0; i < N; i++) {
        int r = rand();
        if (r % 2)
            headCount++;
    }
    return headCount;
}

#endif //DATASTRUCTURE_NUM_H
