//
// Created by proffl on 2021/12/23.
//

#ifndef TINYTENSOR_EXPRESSIONTREE_H
#define TINYTENSOR_EXPRESSIONTREE_H

#include "Operators.h"

typedef double (*Func)(double, double);
namespace autodiff {
    enum class TreeNodeType {
        Variable, Function
    };

    class ExpressionTreeNode {
    public:
        ExpressionTreeNode(double v);
        ExpressionTreeNode(Func f);

        virtual ~ExpressionTreeNode() {};

        double forward();

    public:
        ExpressionTreeNode *left;
        ExpressionTreeNode *right;

        TreeNodeType type;
        union {
            double value;
            Func function;
        };
    };
}



#endif //TINYTENSOR_EXPRESSIONTREE_H
