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

template<typename TPara>
void f1(TPara p) {
    cout << "f1: " << p << endl;
}

template<typename TPara>
void f2(const TPara &p) {
    cout << "f2: " << p << endl;
}

template<typename TPara>
void f3(TPara &p) {
    cout << "f3: " << p << endl;
}

template<typename TPara>
void f4(TPara &&p) {
    cout << "f4:" << p << endl;
}

template<typename TPara>
void f5(TPara &&p) {
    cout << "f5:" << p << endl;
    f4(forward(p));
}

template<typename TPara>
void rvalue_only1(TPara &&p) {}

template<typename TPara>
void rvalue_only1(TPara &p) = delete; // it will also delete const int&

// smarter way
template<typename TPara>
void rvalue_only2(TPara &&p) {
    static_assert(is_rvalue_reference<decltype(p)>::value, "This function is only allowed for rvalues!!");
}

auto my_max(auto a, auto b) {
    return a > b ? a : b;
}

int main() {
    cout << "3.0f > 5.0f?" << mm(3.0f, 5.0f) << endl;

    int i = 0;
    int &j = i;
    const int &k = i;
    f1(3);
    f1(i);
    f1(j);
    f1(k);


    f2(3);
    f2(i);
    f2(j);
    f2(k);

    // f3(3);  // can't compile
    f3(i);
    f3(j);
    f3(k);
    return 0;
}