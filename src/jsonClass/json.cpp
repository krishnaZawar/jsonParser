#include<iostream>
#include<unordered_map>
#include<vector>
#include "valueTypes.h"

#ifndef JSON_class
#define JSON_class

using std::ostream;
using std::string;
using std::unordered_map;
using std::vector;
using std::cout;
using std::endl;

class JSON {    
    public:
        friend ostream& operator<< (ostream&, const JSON&);
        class Object {
            private:
                unordered_map<string, JSON> object;
            public:
                Object() {}

                JSON getKey(string key){
                    if(!findKey(key)){
                        throw string("Error : key not found");
                    }
                    return object[key];
                }

                bool findKey(string key){
                    return object.find(key) != object.end();
                }
                
                void setKey(string key, JSON value){
                    object[key] = value;
                }

                unordered_map<string, JSON> get() const {
                    return object;
                }
        };

        class Array {
            private:
                vector<JSON> array;
            
            public:
                Array() {}

                JSON getIndex(int idx){
                    if(idx >= array.size() || idx < 0){
                        throw string("Error : array index out of bounds");
                    }
                    return array[idx];
                }

                vector<JSON> get() const {
                    return array;
                }

                void append(JSON value){
                    array.push_back(value);
                }
        };

        class Number{
            private:
                long double number;
            public:
                Number() {}
                Number(long double _num) {
                    number = _num;
                }

                long double getNumber(){
                    return number;
                }
        };
    
    private:
        int root_type;

        string str;
        Number number;
        bool boolean;
        Object object;
        Array array;

        void assertRoot(int type) const {
            if(root_type != type){
                throw string("Error : invalid access in JSON");
            }
        } 

        void printValue(JSON &value) const {
            switch(value.getType()){
                case STRING_TYPE:
                    cout << value.getString();
                    break;
                case NUMBER_TYPE:
                    cout << value.getNumber().getNumber();
                    break;
                case NULL_TYPE:
                    cout << "null";
                    break;
                case BOOLEAN_TYPE:
                    cout << (value.getBoolean()? "true" : "false");
                    break;
                case OBJECT_TYPE:
                    value.print();
                    break;
                case ARRAY_TYPE:
                    value.print();
                    break;
                default:
                    throw string("Error : invalid type");
            }
        }

    public:
        // null constructor
        JSON(){
            root_type = NULL_TYPE;
        }
        // string constructor
        JSON(string string_value){
            root_type = STRING_TYPE;
            str = string_value;
        }
        // boolean constructor
        JSON(bool boolean_value){
            root_type = BOOLEAN_TYPE;
            boolean = boolean_value;
        }
        // number constructor
        JSON(Number number_value){
            root_type = NUMBER_TYPE;
            number = number_value;
        } 
        // array constructor
        JSON(Array array_value){
            root_type = ARRAY_TYPE;
            array = array_value;
        }
        // object constructor
        JSON(Object object_value){
            root_type = OBJECT_TYPE;
            object = object_value;
        }

        
        Number getNumber() const {
            assertRoot(NUMBER_TYPE);
            return number;
        } 
        string getString() const {
            assertRoot(STRING_TYPE);
            return "\"" + str + "\"";
        }
        bool getBoolean() const {
            assertRoot(BOOLEAN_TYPE);
            return boolean;
        }
        JSON getKey(string key){
            assertRoot(OBJECT_TYPE);
            return object.getKey(key);
        }
        JSON getIndex(int idx){
            assertRoot(ARRAY_TYPE);
            return array.getIndex(idx);
        }

        void setKey(string key, JSON value){
            object.setKey(key, value);
        }
        void append(JSON value){
            array.append(value);
        }

        int getType() const {
            return root_type;
        }

        void print() const {
            int counter = 0;
            if(root_type == ARRAY_TYPE){
                cout<<"[";
                for(auto &value : array.get()){
                    printValue(value);
                    if(counter < array.get().size()-1){
                        cout<< ", ";
                    }
                    counter++;
                }
                cout << "]";
            }
            else if(root_type == OBJECT_TYPE){
                cout << "{" << endl;
                for(auto &[key, value] : object.get()){
                    cout << "\"" << key << "\" : ";
                    printValue(value);
                    if(counter < object.get().size()-1){
                        cout << "," << endl;
                    }
                    else{
                        cout<<endl;
                    }
                    counter++;
                }
                cout<<"}"<<endl;
            }
            else{
                throw string("Error : print() can be used only on JSON and Array objects");
            }
        }
};

ostream& operator<< (ostream &os, const JSON &json) {
    switch(json.getType()){
        case STRING_TYPE:
            os << json.getString();
            break;
        case NUMBER_TYPE:
            os << json.getNumber();
            break;
        case BOOLEAN_TYPE:
            os << (json.getBoolean()? "true" : "false");
            break;
        case NULL_TYPE:
            os << "null";
            break;
    }
    return os;
}   

#endif // JSON_class