#include <bit/stdc++.h>

using namespace std;

struct A{
    int a;
};
struct AB {
    int a, b;
};

struct Ab {
    int a;
    char b;
};

#define OUT(x) setw(4) << #x << setw(8) << sizeof(x) << setw(8)<< alignof(x) << '\n'

int main() {
    cout << "Name   sizeof   alignof\n";
    cout << OUT(A)
        << OUT(AB)
        << OUT(Ab);
    return 0;
}
