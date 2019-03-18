#include "cpp_json.h"
#include <iostream>
int main() {

	//get cpp_json version
	std::cout << getAPIVersion() << std::endl;

	//create JsonArray
	JsonArray A;
	A.JsonAddIntToArray(1);
	A.JsonAddStringToArray("john");
	A.JsonAddDoubleToArray(8.55);
	A.JsonAddBoolToArray(false);
	//JsonArray to JsonArrayString
	std::string arr1 = A.JsonPrintArray();
	std::cout << "arr1" << std::endl;
	std::cout << arr1 << std::endl;
	std::cout << std::endl;

	//create JsonObject
	JsonObject a;
	a.JsonAddIntToObject("one", 15);
	a.JsonAddStringToObject("two", "johntool");
	a.JsonAddDoubleToObject("three", 99.6999);
	a.JsonAddBoolToObject("four", true);
	//JsonObject to JsonObjectString
	std::string obj1 = a.JsonPrintObject();
	std::cout << "obj1" << std::endl;
	std::cout << obj1 << std::endl;
	std::cout << std::endl;


	JsonArray B;
	//add JsonArray type
	B.JsonAddArrayToArray(A);
	//add JsonObject type
	B.JsonAddObjectToArray(a);
	//add array string type
	B.JsonAddArrayStringToArray("[1,2,3,5.5,\"hello\"]");
	//add object string type
	B.JsonAddObjectStringToArray("{\"q\":888,\"w\":\"iphone\"}");
	std::string arr2 = B.JsonPrintArray();
	std::cout << "arr2" << std::endl;
	std::cout << arr2 << std::endl;
	std::cout << std::endl;


	JsonObject b;
	b.JsonAddArrayToObject("arr1", A);
	b.JsonAddObjectToObject("obj1", a);
	b.JsonAddArrayStringToObject("arr2", arr2);
	b.JsonAddObjectStringToObject("obj2", obj1);
	std::string obj2 = b.JsonPrintObject();
	std::cout << "obj2" << std::endl;
	std::cout << obj2 << std::endl;
	std::cout << std::endl;

	//get array item from index and choose type
	std::cout << A.JsonGetIntFromArray(0) << std::endl;
	std::cout << A.JsonGetStringFromArray(1) << std::endl;
	std::cout << A.JsonGetDoubleFromArray(2) << std::endl;
	std::cout << B.JsonGetArrayStringFromArray(0) << std::endl;
	std::cout << B.JsonGetObjectStringFromArray(1) << std::endl;
	std::cout << std::endl;

	//get JsonArray from array item
	JsonArray C = B.JsonGetArrayFromArray(2);
	std::cout << C.JsonGetStringFromArray(3) << std::endl;
	std::cout << std::endl;

	//get JsonObject from array item
	JsonObject c = B.JsonGetObjectFromArray(3);
	std::cout << c.JsonGetStringFromObject("w") << std::endl;
	std::cout << std::endl;

	//parse json array string to JsonArray
	JsonArray D = D.JsonParseArray(arr2);
	std::cout << D.JsonGetStringFromArray(2) << std::endl;
	std::cout << std::endl;

	//parse json object string to JsonObject
	JsonObject d = d.JsonParseObject(obj2);
	d.JsonAddObjectToObject("obj3", b);
	std::cout << d.JsonGetObjectStringFromObject("obj2") << std::endl;
	std::cout << d.JsonGetObjectStringFromObject("obj3") << std::endl;
	std::cout << d.JsonGetArrayStringFromObject("arr1") << std::endl;
	std::cout << d.JsonGetArrayStringFromObject("arr2") << std::endl;
	std::cout << std::endl;

	//get JsonArray from JsonObject item
	JsonArray E = d.JsonGetArrayFromObject("arr2");
	std::cout << "arr2" << std::endl;
	std::cout << E.JsonPrintArray() << std::endl;
	std::cout << E.JsonGetArrayStringFromArray(0) << std::endl;

	//get JsonArray from JsonArray item
	JsonArray F = E.JsonGetArrayFromArray(0);
	std::cout << F.JsonGetStringFromArray(1) << std::endl;
	std::cout << F.JsonGetDoubleFromArray(2) << std::endl;
	std::cout << F.JsonGetBoolFromArray(3) << std::endl;
	std::cout << std::endl;

	//get JsonObject from JsonObject item
	JsonObject e = d.JsonGetObjectFromObject("obj2");
	std::cout << "new obj2" << std::endl;
	std::cout << e.JsonPrintObject() << std::endl;
	std::cout << e.JsonGetDoubleFromObject("three") << std::endl;
	std::cout << std::endl;

	//delete JsonArray content
	A.JsonDeleteArray();
	std::cout << A.JsonPrintArray() << std::endl;

	//delete JsonObject content
	a.JsonDeleteObject();
	std::cout << a.JsonPrintObject() << std::endl;

	system("pause");
	return 0;
}