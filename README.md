
# <p align = "center">JSON Parser</p>
This is a read-only JSON Parser written for C++. It allows the user to parse the JSON effectively via functions.
Note : This JSON parser only accepts an Object or an Array on the root level.
## JSON interface
```
class JSON:
	// get functions
	Number getNumber()
	string getString()
	bool getBoolean()
	JSON getKey(string key)
	JSON getObject()
	JSON getIndex(int idx)
	JSON getArray()
	int getType()

	// set functions
	void setKey(string key, JSON value)
	void append(JSON value)
	
	// print the complete JSON
	void print()
```
the "getType()" tells us the type of JSON, i.e, whether the JSON is an object, array, string, boolean, number or null.

Every get function returns a value only if the type matches the get function, i.e, a JSON object of type String can only be accessed via "getString()" .

Similarly "setKey()" and "append()" can be used only with Object and Array types respectively.

"print()" function can be used only with Object or Array types.

## How to use
let us take an example JSON
```
{
	"name" : "abcd",
	"age" : 21,
	"cgpa" : 9.12,
	"degree_completed" : false,
	"backlogs" : null,
	"hobbies" : ["cricket", "badminton", "kubernetes"]
}
```
Add this JSON in the "testFile.json".
Then write your code logic in the try block given in the "main.cpp" file.
```
try{
	JSON obj = parser.parse(input);
	/*
		Your code logic
	*/
}
catch(string  &err){
	cout<<err<<endl;
}
catch(exception &e){
	cout<<e.what()<<endl;
}
```
Then run the following command to compile the project
```
g++ src/main.cpp -o main
```
To run the project write
```
./main.exe
```
## Future Scope
1. Allow persistent updates on the JSON via the parser.
2. Modularize the parser for easy exports.




