#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#define Version "cpp_json_v1.0_20190124_by_john"
#define TypeInt 1<<1
#define TypeString 1<<2
#define TypeDouble 1<<3
#define TypeArray 1<<4
#define TypeObject 1<<5
#define TypeArrayString 1<<6
#define TypeObjectString 1<<7
#define TypeBool 1<<8

std::string getAPIVersion();

class JsonObject;
class JsonArray {
public:
	JsonArray();

	//array
	void JsonAddIntToArray(int);
	void JsonAddStringToArray(std::string);
	void JsonAddDoubleToArray(double);
	void JsonAddBoolToArray(bool);
	void JsonAddArrayStringToArray(std::string);
	void JsonAddObjectStringToArray(std::string);
	void JsonAddArrayToArray(JsonArray);
	void JsonAddObjectToArray(JsonObject);
	std::string JsonPrintArray();
	JsonArray JsonParseArray(std::string);
	int JsonGetArraySize();
	int JsonGetIntFromArray(int);
	std::string JsonGetStringFromArray(int);
	double JsonGetDoubleFromArray(int);
	bool JsonGetBoolFromArray(int);
	JsonArray JsonGetArrayFromArray(int);
	JsonObject JsonGetObjectFromArray(int);
	std::string JsonGetArrayStringFromArray(int);
	std::string JsonGetObjectStringFromArray(int);
	void JsonDeleteArray();

private:
	std::vector<std::string> array;
	std::vector<int> type;
};

class JsonObject {
public:
	JsonObject();

	//object
	void JsonAddIntToObject(std::string, int);
	void JsonAddStringToObject(std::string, std::string);
	void JsonAddDoubleToObject(std::string, double);
	void JsonAddBoolToObject(std::string, bool);
	void JsonAddArrayStringToObject(std::string, std::string);
	void JsonAddObjectStringToObject(std::string, std::string);
	void JsonAddArrayToObject(std::string, JsonArray);
	void JsonAddObjectToObject(std::string, JsonObject);
	std::string JsonPrintObject();
	JsonObject JsonParseObject(std::string);
	int JsonGetIntFromObject(std::string);
	std::string JsonGetStringFromObject(std::string);
	double JsonGetDoubleFromObject(std::string);
	bool JsonGetBoolFromObject(std::string);
	JsonArray JsonGetArrayFromObject(std::string);
	JsonObject JsonGetObjectFromObject(std::string);
	std::string JsonGetArrayStringFromObject(std::string);
	std::string JsonGetObjectStringFromObject(std::string);
	void JsonDeleteObject();

private:
	std::vector<std::string> obj_key;
	std::vector<std::string> obj_value;
	std::vector<int> type;
};