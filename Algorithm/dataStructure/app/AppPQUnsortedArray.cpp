#include <iostream>
#include "PQUnsortedArray.h"

using namespace std;

int main() {
    PQUnsortedArray<int> queue;
    int x = 5;
    queue.insert(&x, 5);
    int y = 4;
    queue.insert(&y, 4);
    int z = 6;
    queue.insert(&z, 6);
    while (!queue.isEmpty()) {
        cout << *queue.peek() << endl;
    }

    PQUnsortedArray<char*> queue2;

    char *bug1 = new char[]{"Hello world!"};
    queue2.insert(&bug1, 1);
    char * bug2 = new char[]{"Unencrypted password on DB"};
    queue2.insert(&bug2, 10);
    char * bug3 = new char[]{"UI breaks on browser X"};
    queue2.insert(&bug3, 9);

    while (!queue2.isEmpty()) {
        char** str = queue2.peek();
        cout << (*str) << endl;
    }

    return 0;
}
