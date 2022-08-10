#include <iostream>
#include "Num.h"
using namespace std;

int main() {
    cout << "INT MAX value = " << findMax<int>() << endl;
    cout << "INT MIN value = " << findMin<int>() << endl << endl;

    cout << "LONG MAX value = " << findMax<long>() << endl;
    cout << "LONG MIN value = " << findMin<long>() << endl << endl;

    cout << "SHORT MAX value = " << findMax<short>() << endl;
    cout << "SHORT MIN value = " << findMin<short>() << endl << endl;

    cout << "DOUBLE MAX value = " << findMax<double>() << endl;
    cout << "DOUBLE MIN value = " << findMin<double>() << endl << endl;

    cout << "FLOAT MAX value = " << findMax<float>() << endl;
    cout << "FLOAT MIN value = " << findMin<float>() << endl << endl;

    int r[]{10, 100, 1000};
    int N[]{1000, 10000, 100000, 1000000};
    for (auto& i : r) {
        for (auto& j : N) {
            cout << "r=" << i << ", N=" << j << " standard deviation = " << randTest(i, j) << endl;
        }
    }

    float sumArea = 0.f;
    for (int i = 0; i < 100; i++) {
        Triangle triangle = Triangle::rand();
        sumArea += triangle.area();
    }
    cout << "average area = " << sumArea / 100 << endl;

    printPrimes(1000);

    int t = 32;
    vector<int> distribution(t+1, 0);
    for (int i = 0; i < 10000; i++) {
        distribution[coinFlipSimulation(t)]++;
    }
    for (int i = 0; i <= t; i++) {
        cout << i << " -> " << distribution[i] << endl;
    }
    return 0;
}
