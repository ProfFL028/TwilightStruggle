#include <iostream>
#include "autodiff/Operators.h"
#include "autodiff/ExpressionTree.h"
#include "reg/Regression.h"

using namespace autodiff;
using namespace reg;
using namespace std;

int main() {
    string expr = "53.5 * 621. + 09 * sigmoid(07.3)";
    int exprLen = expr.size();

    string s = "136.56E34";

    TokenMachine tokenMachine(s);
    Token* token = tokenMachine.next();
    if (token->name == TokenName::Number) {
        NumberToken* nt = static_cast<NumberToken*>(token);
        cout << nt->value << endl;
    }

    return 0;
}
