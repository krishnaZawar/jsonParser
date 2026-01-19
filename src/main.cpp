#include <iostream>
#include <fstream>
#include "parser/parser.cpp"
#include "jsonClass/json.cpp"

using std::string;
using std::ifstream;
using std::getline;
using std::cout;
using std::endl;
using std::exception;

int main(){
    Parser parser = Parser();
    
    ifstream file("testFile.json");
    
    string input = "";
    string buffer = "";

    while(getline(file, buffer)){
        input += buffer + "\n";
    }

    try{
        JSON obj = parser.parse(input);
        obj.print();
    }
    catch(string &err){
        cout<<err<<endl;
    }
    catch(exception &e){
        cout<<e.what()<<endl;
    }
}