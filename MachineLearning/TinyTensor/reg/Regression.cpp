//
// Created by proffl on 2021/12/25.
//

#include "Regression.h"
#include "../util/StringUtil.h"
#include <math.h>

using namespace reg;
using namespace util;


const Token *WordToken::Err = new WordToken(TokenName::Err, "\0");
const Token *WordToken::End = new WordToken(TokenName::End, "\0");
const Token *WordToken::Add = new WordToken(TokenName::Add, "+");
const Token *WordToken::Minus = new WordToken(TokenName::Minus, "-");
const Token *WordToken::Div = new WordToken(TokenName::Div, "/");
const Token *WordToken::Mul = new WordToken(TokenName::Mul, "*");


const double NumberToken::NUMBER_BASE = 10;

Token::Token(TokenName n) {
    this->name = n;
}


TokenMachine::TokenMachine(string expression) {
    this->expression = expression;
    this->currentIdx = 0;
}

Token *TokenMachine::next() {
    char currentChar = expression[currentIdx];
    switch (currentChar) {
        case '+':
            return const_cast<Token *>(WordToken::Add);
        case '-':
            return const_cast<Token *>(WordToken::Minus);
        case '/':
            return const_cast<Token *>(WordToken::Div);
        case '*':
            return const_cast<Token *>(WordToken::Mul);
    }
    if (CharacterUtil::isDigit(currentChar)) {
        return this->getNextNumber();
    }

    return const_cast<Token *>(WordToken::End);
}

Token *TokenMachine::getNextNumber() {
    double value = getIntPart();
    cout << currentIdx << ", " << expression[currentIdx] << endl;
    if (expression[currentIdx] == '.') {
        currentIdx++;
        value += getFloatPart();
    }
    if (expression[currentIdx] == 'e' || expression[currentIdx] == 'E') {
        currentIdx++;
        int basePow = getIntPart();
        value *= pow(NumberToken::NUMBER_BASE, basePow);
    }

    return new NumberToken(value);
}

double TokenMachine::getFloatPart() {
    char currentChar = expression[currentIdx];
    double base = 1.0 / NumberToken::NUMBER_BASE;
    double value = 0;
    while (CharacterUtil::isDigit(currentChar)) {
        value += (currentChar - '0') * base;
        base /= NumberToken::NUMBER_BASE;

        currentChar = expression[++currentIdx];
    }
    return value;
}

int TokenMachine::getIntPart() {
    char currentChar = expression[currentIdx];
    int value = 0;
    while (CharacterUtil::isDigit(currentChar)) {
        value *= NumberToken::NUMBER_BASE;
        value += (currentChar - '0');

        currentChar = expression[++currentIdx];
    }
    return value;
}




