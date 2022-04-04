#include <Sort.h>
#include <iostream>

using namespace std;

int main() {
    ds::Vector<int> vec;
    int arr[] {5,1,7,8,2,3,4,1,7,3,5};
    for (auto i : arr) {
        vec.insert(i);
    }
    cout << vec << endl;
    // TODO: we need to track head and tail.
    auto top = &vec.head;
    auto end = vec.tail->next;
    auto cur = (*top)->next;
    auto pivot = *top;
    auto pre = pivot;
    while (cur != end) {
        if (cur->element < pivot->element) {
            pre->next = cur->next;
            cur->next = *top;
            *top = cur;
            cur = pre->next;
        } else if (cur->element == pivot->element) {
            pre->next = cur->next;
            cur->next = pivot->next;
            pivot->next = cur;
            cur = pre->next;
        } else {
            pre = cur;
            cur = cur->next;
        }
    }
    vec.tail = pre;
    cout << vec << endl;

    int a = 5;
    int b = 6;
    swap(a, b);
    cout << a << " " << b << endl;

    int stack[STACK_SIZE];
    cout << sizeof(size_t) << endl;
    cout << CHAR_BIT << endl;
    cout << STACK_SIZE << endl;
}