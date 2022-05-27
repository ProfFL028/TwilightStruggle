#include <iostream>

using namespace std;

void gradient_descent(double *x, double *y, double lr, double eps,
                      double(*f)(double, double),
                      double(*gx)(double, double),
                      double(*gy)(double, double)) {
    double val = f(*x, *y), delta;
    do {
        *x -= lr * gx(*x, *y);
        *y -= lr * gy(*x, *y);
        double newValue = f(*x, *y);
        delta = abs(newValue - val);
        val = newValue;
    } while (delta > eps);
}

template<typename T, typename LR, typename EPS, typename F, typename G>
T gradient_descent_template(T x, LR lr, EPS eps, F f, G g) {
    auto value = f(x), delta = value;
    do {
        x -= lr * g(x);
        auto newValue = f(x);
        delta = abs(newValue - value);
        value = newValue;
    } while (delta > eps);
    return x;
}

int main() {
    auto f = [](double x, double y) {
        return x * x - x + y * y - y;
    };
    auto gx = [](double x, double y) {
        return 2 * x - 1;
    };
    auto gy = [](double x, double y) {
        return 2 * y - 1;
    };

    double x = 1, y = 1, eps = 0.001;
    gradient_descent(&x, &y, 0.01, eps, f, gx, gy);
    return 0;
}