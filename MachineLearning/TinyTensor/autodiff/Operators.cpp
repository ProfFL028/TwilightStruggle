//
// Created by proffl on 2021/12/23.
//

#include "Operators.h"
#include <math.h>

double Add::forward(double a, double b) {
    return a + b;
}

double Minus::forward(double a, double b) {
    return a - b;
}

double Mul::forward(double a, double b) {
    return a * b;
}

double Div::forward(double a, double b) {
    return a / b;
}

double Sigmoid::forward(double a, double b) {
    return 1.0 / (1.0 + exp(-a));
}
