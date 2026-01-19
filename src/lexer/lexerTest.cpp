#include "lexer.cpp"
#include "../token/token.cpp"
#include<iostream>
#include<vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;


void numberTest(Lexer lexer, string JSON, Token token){
    vector<string> validTests = {"0", "-0", "0.00", "-0.00", "0E00", "-0E00", "0.0e+1", "-0.0e-1", "123", "-123", "213.213", "-23123.2312", "231e123", "-2131e12321", "231.23e123", "-4523.3512213e34342134"};
    vector<string> invalidTests = { "-", "00", ".", "-.3123", "-e23", "-e", ".323", "e2312", "e", "E+", "1e12.231"};

    lexer.tokenize(JSON);

    int counter = 1;

    //valid tests
    for(auto &test : validTests){
        JSON = test;
        lexer.tokenize(JSON);
        do{
            try{
                token = lexer.getNextToken();
                if(token.type == NUMBER_TOKEN && token.value == JSON){
                    cout<<"number test "<<counter<<": passed"<<endl;
                }
                else if(token.type != END_OF_FILE_TOKEN){
                    cout<<"number test "<<counter<<": failed"<<endl;
                }
            }
            catch(std::string err){
                cout<<"number test "<<counter<<": failed"<<endl;
                break;
            }
        }while(token.type != END_OF_FILE_TOKEN);
        counter++;
    }

    //invalid tests
    for(auto &test : invalidTests){
        JSON = test;
        lexer.tokenize(JSON);
        do{
            try{
                token = lexer.getNextToken();
                if(token.type == NUMBER_TOKEN && token.value == JSON){
                    cout<<"number test "<<counter<<": failed"<<endl;
                }
            }
            catch(std::string err){
                cout<<"number test "<<counter<<": passed"<<endl;
                break;
            }
        }while(token.type != END_OF_FILE_TOKEN);
        counter++;
    }
}

void stringTest(Lexer lexer, string JSON, Token token){
    /*
        Test 1 : valid string
        Test 2 : invalid string
    */
    JSON = "\"abcd\" \"abcd";
    lexer.tokenize(JSON);
    
    try{
        token = lexer.getNextToken();
        if(token.type == STRING_TOKEN && token.value == "abcd"){
            cout<<"string test 1: passed"<<endl;
        }
        else{
            cout<<"string test 1: failed"<<endl;
        }
    }
    catch(std::string err){
        cout<<"string test 1: failed"<<endl;
    }
    try{
        token = lexer.getNextToken();
        cout<<"string test 2: failed"<<endl;
    }
    catch(std::string err){
        if(err == "Error : could not parse string"){
            cout<<"string test 2: passed"<<endl;
        }
        else{
            cout<<"string test 2: failed"<<endl;
        }
    }
    catch(...){}
}

void lexerTest(){
    Lexer lexer = Lexer();

    string JSON = "";
    Token token;

    stringTest(lexer, JSON, token);
    cout<<endl;
    numberTest(lexer, JSON, token);
}
