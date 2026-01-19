#include "tokenType.h"
#include<iostream>

#ifndef Token_class
#define Token_class

class Token{
    public:
        TokenType type;
        std::string value;

        Token() {}

        Token(TokenType _type, std::string _value){
            type = _type;
            value = _value;
        }
};

#endif // Token_class