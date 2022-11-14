#include <memory>
#include <iostream>
using namespace std;

int main() {
    unique_ptr<double> dp { new double};
    *dp = 7;
    cout << "The value of *dp=" << *dp << endl;
    return 0;
}