//
// Created by proffl on 2021/12/23.
//

#include "ExpressionTree.h"
#include <iostream>

using namespace autodiff;
using namespace std;

ExpressionTreeNode::ExpressionTreeNode(double v) {
    this->type = TreeNodeType::Variable;
    this->value = v;
}

ExpressionTreeNode::ExpressionTreeNode(Func f) {
    this->type = TreeNodeType::Function;
    this->function = f;
}

double ExpressionTreeNode::forward() {
    switch (this->type) {
        case TreeNodeType::Variable:
            return this->value;

        case TreeNodeType::Function:
            return this->function(this->left->forward(), this->right->forward());
        default:
            cerr << "ExpressionTreeNode should be Variable or Function!" << endl;

    }
    return 0;
}
