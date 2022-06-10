#include <iostream>
#include <valarray>
using namespace std;

int main() {
    valarray<float> v1={1,2,3}, v2={7,8,9}, v3=v1 + 2.0f * v2;
    v1 = sin(v3);
    for (auto x : v1) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}