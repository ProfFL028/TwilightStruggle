#include <iostream>

using namespace std;

template<typename T>
inline T mm(T a, T b) {
    // return a > b ? a.value : b.value; it can be compiled, but may suffer runtime error.
    return a > b ? a : b;
}

// we can also add const T& to it too.
//template<typename T>
//inline T mm(const T& a, const T& b) {
//    return a > b ? a : b;
//}

template <typename TPara>
void f1(TPara p) {
    cout << p << endl;
}

int main() {
    cout << "3.0f > 5.0f?" << mm(3.0f, 5.0f) << endl;

    int i = 0;
    int& j = i;
    const int& k = i;
    f1(3);
    f1(i);
    f1(j);
    f1(k);
    return 0;
}