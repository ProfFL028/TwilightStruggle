#include <Sort.h>
#include <iostream>

using namespace std;

int main() {
    int a = 5;
    int b = 6;
    swap(a, b);
    cout << a << " " << b << endl;

    int stack[STACK_SIZE];
    cout << sizeof(size_t) << endl;
    cout << CHAR_BIT << endl;
    cout << STACK_SIZE << endl;

    ds::Vector<int> vec;
    vec.insert(5);
    vec.insert(6);
    cout << "before swap" << endl;
    cout << vec << endl;
    swap(vec.head->element, vec.head->next->element);
    cout << "after swap" << endl;
    cout << vec << endl;
}