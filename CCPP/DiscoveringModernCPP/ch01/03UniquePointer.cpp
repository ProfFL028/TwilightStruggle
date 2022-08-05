
#include <iostream>
#include <memory>
using namespace std;

int main() {
    unique_ptr<double> dp{new double};
    *dp = 7;
    cout << *dp << endl;

    unique_ptr<double> dp2{move(dp)}, dp3;
    dp3 = move(dp2);
    *dp3 = 2;
    // cout << "the value of dp1 is: " << *dp << endl; // error
    cout << "the value of dp3 is: " << *dp3 << endl;
    return 0;
}