//
// Created by proffl on 2021/12/25.
//

#ifndef TINYTENSOR_REGRESSION_H
#define TINYTENSOR_REGRESSION_H

#include <iostream>

namespace reg {
    using namespace std;
    enum class TokenName {
        Err, Number, Word, Add, Minus, Mul, Div, Eq, LeftBracket, RightBracket, WS, Dot, End
    };

    class Token {
    public:
        Token(TokenName n);

        virtual ~Token() {}

        TokenName name;
    };

    class NumberToken final : public Token {
    public:
        NumberToken(double v) : Token(TokenName::Number), value(v) {};

        virtual ~NumberToken() {};

        double value;
        const static double NUMBER_BASE;
    };

    class WordToken final : public Token {
    public:
        WordToken(string v) : Token(TokenName::Word), value(v) {};

        WordToken(TokenName n, string v) : Token(n), value(v) {};

        virtual ~WordToken() {};
    public:
        string value;

    public:
        static const Token *Err;
        static const Token *End;
        static const Token *Add;
        static const Token *Minus;
        static const Token *Div;
        static const Token *Mul;
    };

    class TokenMachine final {
    public:
        Token *next();

    private:
        Token *getNextNumber();

        int getIntPart();

        double getFloatPart();

    private:
        int currentIdx;
        string expression;
    public:
        TokenMachine(string expression);

        virtual ~TokenMachine() {};
    };
}


#endif //TINYTENSOR_REGRESSION_H
