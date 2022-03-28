#include "Hash.h"
#include <iostream>

using namespace std;

int main() {
    const char *url = "http://helloworld.com";

    uint32_t* result = new uint32_t();
    murmurHash_32(url, 23, 1, result);
    cout << *result << endl;

    auto result64 = new uint64_t ();
    murmurHash_x86_128(url, 23, 1, result64);
    cout << *result64 << endl;

    murmurHash_x64_128(url, 23, 1, result64);
    cout << *result64 << endl;

    return 0;
}
