//
// Created by proffl on 2021/12/23.
//

#ifndef TINYTENSOR_OPERATORS_H
#define TINYTENSOR_OPERATORS_H


class OperatorBase {
public:
    static double calc(double a, double b);
};

class Add: public OperatorBase {
public:
    static double calc(double a, double b);
};

class Sub: public OperatorBase {
public:
    static double calc(double a, double b);
};

class Mul: public OperatorBase {
public:
    static double calc(double a, double b);
};

class Div: public OperatorBase {
public:
    static double calc(double a, double b);
};




#endif //TINYTENSOR_OPERATORS_H
