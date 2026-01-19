#include "../token/tokenType.h"
#include "../token/token.cpp"
#include<iostream>
#include<vector>

#ifndef Lexer_class
#define Lexer_class

class Lexer{
    private:
        std::string text;
        int ptr;

        std::vector<char> skippables;

        template<class t>
        bool existsIn(std::vector<t> &arr, t val){
            for(auto &_val : arr){
                if(val == _val){
                    return true;
                }
            }
            return false;
        }

        inline bool isDigit(char &ch){
            return ch >= '0' && ch <= '9';
        }
        inline bool isAlpha(char &ch){
            return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
        }

        Token getNumber(){
            /*
                number regex :
                    Fraction : .[0-9]+ 
                    Exponent : (e|E)(+|-)?[0-9]+
                    Number : -?([0]Fraction?Exponent? | [1-9][0-9]*Fraction?Exponent?)
            */
            if(text[ptr] != '-' && !isDigit(text[ptr])){
                throw std::string("Error : could not parse number");
            }
            std::string value = "";
            value += text[ptr];
            ptr++;
            if(value == "-"){
                if(ptr >= text.size() || !isDigit(text[ptr])){
                    throw std::string("Error : could not parse number");
                }
                value += text[ptr];
                ptr++;
            }

            if(value.back() == '0' && (ptr < text.size() && isDigit(text[ptr]))){
                throw std::string("Error : could not parse number");
            }
            while(ptr < text.size() && isDigit(text[ptr])){
                value += text[ptr];
                ptr++;
            }
            
            //fraction
            if(ptr < text.size() && text[ptr] == '.'){
                value += ".";
                ptr++;
                while(ptr < text.size() && isDigit(text[ptr])){
                    value += text[ptr];
                    ptr++;
                }

                if(!isDigit(value.back())){
                    throw std::string("Error : could not parse number");
                }
            }
            
            //exponent 
            if(ptr < text.size() && (text[ptr] == 'e' || text[ptr] == 'E')){
                value += text[ptr];
                ptr++;
                if(ptr < text.size() && (text[ptr] == '-' || text[ptr] == '+')){
                    value += text[ptr];
                    ptr++;
                }
                while(ptr < text.size() && isDigit(text[ptr])){
                    value += text[ptr];
                    ptr++;
                }

                if(!isDigit(value.back())){
                    throw std::string("Error : could not parse number");
                }
            }

            return Token(NUMBER_TOKEN, value);
        }
        
    public:
        Lexer() {
            text = "";
            ptr = 0;

            skippables = {
                ' ', '\n', '\t', '\r'
            };
        }

        Token getNextToken() {
            while(ptr < text.size() && existsIn(skippables, text[ptr])){
                ptr++;
            }
            if(ptr >= text.size()){
                return Token(END_OF_FILE_TOKEN, "");
            }
            
            switch(text[ptr]){
                case '{':
                    ptr++;
                    return Token(OPEN_CURLY_PARENTHESIS_TOKEN, "{");
                case '}':
                    ptr++;
                    return Token(CLOSE_CURLY_PARENTHESIS_TOKEN, "}");
                case '[':
                    ptr++;
                    return Token(OPEN_SQUARE_PARENTHESIS_TOKEN, "[");
                case ']':
                    ptr++;
                    return Token(CLOSE_SQUARE_PARENTHESIS_TOKEN, "]");
                case ':':
                    ptr++;
                    return Token(COLON_TOKEN, ":");
                case ',':
                    ptr++;
                    return Token(COMMA_TOKEN, ",");
            }
            
            if(text[ptr] == '\"'){
                std::string value = "";
                ptr++;
                while(ptr < text.size() && text[ptr] != '\"'){
                    value += text[ptr];
                    ptr++;
                }
                if(ptr == text.length()){
                    throw std::string("Error : could not parse string");
                }
                ptr++;
                return Token(STRING_TOKEN, value);
            }

            if(isAlpha(text[ptr])){
                std::string value = "";
                while(ptr < text.size() && isAlpha(text[ptr])){
                    value += text[ptr];
                    ptr++;
                }
                if(value == "null"){
                    return Token(NULL_TOKEN, value);
                }
                if(value == "true" || value == "false"){
                    return Token(BOOLEAN_TOKEN, value);
                }
                throw std::string("Error : Invalid keyword");
            }
            
            return getNumber();
        }

        void tokenize(std::string _text){
            text = _text;
            ptr = 0;
        }
};

#endif // Lexer_class