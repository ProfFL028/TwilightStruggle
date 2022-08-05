#include <iostream>
#include <math.h>

//double fin_diff(double f(double), double x, double h) {
//    return (f(x + h) - f(x)) / h;
//}

double sin_plus_cos(double x) {
    return sin(x) + cos(x);
}

struct sc_f {
    double operator()(double x) const {
        return sin(x) + cos(x);
    }
};

class psc_f {
public:
    explicit psc_f(double alpha) : alpha{alpha} {}

    double operator()(double x) const {
        return sin(alpha * x) + cos(x);
    }

private:
    double alpha;
};

template<typename F, typename T>
T inline fin_diff(F f, const T &x, const T &h) {
    return (f(x + h) - f(x));
}

int main() {
    using namespace std;
    psc_f psc1{1.0};
    cout << fin_diff(psc1, 1., 0.001) << endl;
    cout << fin_diff(psc_f{2.0}, 1.0, 0.001) << endl;
    cout << fin_diff(sin_plus_cos, 1., 0.001) << endl;
    return 0;
}