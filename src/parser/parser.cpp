#include <stack>
#include <string>
#include "../lexer/lexer.cpp"
#include "../jsonClass/valueTypes.h"
#include "../token/tokenType.h"
#include "../jsonClass/json.cpp"

#ifndef Parser_class
#define Parser_class

using std::string;
using std::stack;
using std::stold;

class Parser{
    private:
        stack<JSON> call_depth;

        Lexer lexer;
        Token token;

    void eat(TokenType type){
        if(token.type != type){
            throw string("Error : expected token type mismatch");
        }
        token = lexer.getNextToken();
    }

    void parseKeyValuePair(){
        string key = token.value;
        eat(STRING_TOKEN);
        eat(COLON_TOKEN);
        call_depth.top().setKey(key, parseValue());
    }
    void parseObjectBody(){
        parseKeyValuePair();
        while(token.type == COMMA_TOKEN){
            eat(COMMA_TOKEN);
            parseKeyValuePair();
        }
    }
    JSON parseObject(){
        eat(OPEN_CURLY_PARENTHESIS_TOKEN);
        call_depth.push(JSON(JSON::Object()));
        if(token.type != CLOSE_CURLY_PARENTHESIS_TOKEN){
            parseObjectBody();
        }
        JSON obj = call_depth.top();
        call_depth.pop();
        eat(CLOSE_CURLY_PARENTHESIS_TOKEN);
        return obj;
    }

    void parseArrayBody(){
        call_depth.top().append(parseValue());
        while(token.type == COMMA_TOKEN){
            eat(COMMA_TOKEN);
            parseArrayBody();
        }
    }
    JSON parseArray(){
        eat(OPEN_SQUARE_PARENTHESIS_TOKEN);
        call_depth.push(JSON(JSON::Array()));
        if(token.type != CLOSE_SQUARE_PARENTHESIS_TOKEN){
            parseArrayBody();
        }
        JSON obj = call_depth.top();
        call_depth.pop();
        eat(CLOSE_SQUARE_PARENTHESIS_TOKEN);
        return obj;
    }

    JSON parseValue(){
        JSON obj;
        switch(token.type){
            case OPEN_CURLY_PARENTHESIS_TOKEN:
                obj = parseObject();
                break;
            case OPEN_SQUARE_PARENTHESIS_TOKEN:
                obj = parseArray();
                break;
            case STRING_TOKEN:
                obj = JSON(token.value);
                eat(STRING_TOKEN);
                break;
            case NUMBER_TOKEN:
                obj = JSON(JSON::Number(stold(token.value)));
                eat(NUMBER_TOKEN);
                break;
            case BOOLEAN_TOKEN:
                obj = JSON(token.value == "true");
                eat(BOOLEAN_TOKEN);
                break;
            case NULL_TOKEN:
                obj = JSON();
                eat(NULL_TOKEN);
                break;
            default:
                throw string("Error : invalid token");
        }
        return obj;
    }   
    
    public:
        Parser(){
            lexer = Lexer();
        }
        
        JSON parse(string text){
            lexer.tokenize(text);
            token = lexer.getNextToken();

            JSON obj;

            if(token.type == OPEN_CURLY_PARENTHESIS_TOKEN){
                obj = parseObject();
            }
            else if(token.type == OPEN_SQUARE_PARENTHESIS_TOKEN){
                obj = parseArray();
            }
            else{
                throw string("Error : JSON should ba an array or object at root");
            }

            return obj;
        }

};

#endif // Parser_class