#include <iostream>
#include "autodiff/Operators.h"
#include "autodiff/ExpressionTree.h"

using namespace autodiff;
using namespace std;

int main() {
    ExpressionTreeNode x(5);
    ExpressionTreeNode y(6);
    ExpressionTreeNode z(7);

    Func add = &Add::forward;
    ExpressionTreeNode k(add);
    k.left = &x;
    k.right = &y;

    ExpressionTreeNode node2(&Sigmoid::forward);
    node2.left = &z;

    ExpressionTreeNode node3(add);
    node3.left = &k;
    node3.right = &node2;

    cout << (5 + 6) + Sigmoid::forward(7, 0) << endl;
    cout << node3.forward() << endl;


    return 0;
}
