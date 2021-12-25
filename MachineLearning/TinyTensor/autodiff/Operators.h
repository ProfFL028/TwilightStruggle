//
// Created by proffl on 2021/12/23.
//

#ifndef TINYTENSOR_OPERATORS_H
#define TINYTENSOR_OPERATORS_H

#include <tuple>

class OperatorBase {
public:
    static double forward(double a, double b);

protected:
    std::tuple<double> context;
};

class Add: public OperatorBase {
public:
    static double forward(double a, double b);
};

class Sub: public OperatorBase {
public:
    static double forward(double a, double b);
};

class Mul: public OperatorBase {
public:
    static double forward(double a, double b);
};

class Div: public OperatorBase {
public:
    static double forward(double a, double b);
};

class Sigmoid: public OperatorBase {
public:
    static double forward(double a, double b);
};




#endif //TINYTENSOR_OPERATORS_H
