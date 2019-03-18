#include <iostream>
#include "cpp_json.h"

///////////////////////////////////////////////////////JsonArray//////////////////////////////////////////////////////////////

std::string getAPIVersion() {
	return Version;
}

template <class T>
std::string ConvertToString(T value) {
	std::stringstream ss;
	ss << value;
	return ss.str();
}

bool IsDouble(std::string value) {
	for (int i = 0; i < value.size(); i++) {
		if (value[i] == '.') {
			return true;
		}
	}
	return false;
}

JsonArray::JsonArray() {

}

void JsonArray::JsonAddIntToArray(int value) {
	array.push_back(ConvertToString(value));
	type.push_back(TypeInt);
}

void JsonArray::JsonAddStringToArray(std::string value) {
	array.push_back(value);
	type.push_back(TypeString);
}

void JsonArray::JsonAddDoubleToArray(double value) {
	array.push_back(ConvertToString(value));
	type.push_back(TypeDouble);
}

void JsonArray::JsonAddBoolToArray(bool value) {
	if (value) {
		array.push_back("true");
	}
	else {
		array.push_back("false");
	}
	type.push_back(TypeBool);
}
void JsonArray::JsonAddArrayStringToArray(std::string arrstr) {
	array.push_back(arrstr);
	type.push_back(TypeArray);
}

void JsonArray::JsonAddObjectStringToArray(std::string jsonstr) {
	array.push_back(jsonstr);
	type.push_back(TypeObject);
}

void JsonArray::JsonAddArrayToArray(JsonArray arr) {
	array.push_back(arr.JsonPrintArray());
	type.push_back(TypeArray);
}

void JsonArray::JsonAddObjectToArray(JsonObject json) {
	array.push_back(json.JsonPrintObject());
	type.push_back(TypeObject);
}

//JsonArray to string
std::string JsonArray::JsonPrintArray() {
	std::string str;

	for (int i = 0; i < array.size(); i++) {
		if (type[i] == TypeInt) {
			str += array[i];
		}
		else if (type[i] == TypeString) {
			str += '"' + array[i] + '"';
		}
		else if (type[i] == TypeDouble) {
			str += array[i];
		}
		else if (type[i] == TypeBool) {
			str += array[i];
		}
		else if (type[i] == TypeArrayString) {
			str += array[i];
		}
		else if (type[i] == TypeObjectString) {
			str += array[i];
		}
		else if (type[i] == TypeArray) {
			str += array[i];
		}
		else if (type[i] == TypeObject) {
			str += array[i];
		}

		if (i < array.size() - 1) {
			str += ',';
		}
	}

	str = '[' + str + ']';
	return str;
}

//JsonArrayString to JsonArray
JsonArray JsonArray::JsonParseArray(std::string arraystr) {
	JsonArray arr;
	arraystr = arraystr.substr(1, arraystr.size() - 2);
	int valuefirst = 0;
	int valuelast = 0;
	std::string valuestr;
	bool conti = true;
	while (conti) {
		if (arraystr[0] == '"') {
			valuelast = arraystr.find('"', 1);
			if (valuelast == arraystr.size() - 1) {
				valuelast = arraystr.size();
				valuestr = arraystr.substr(1, valuelast - 2);
				arr.JsonAddStringToArray(valuestr);
				break;
			}
			valuestr = arraystr.substr(valuefirst + 1, valuelast - valuefirst - 1);
			arraystr = arraystr.substr(valuelast + 2, arraystr.size());
			arr.JsonAddStringToArray(valuestr);
		}
		else if (arraystr[0] == '[') {
			int last_left = 1;
			int last_right = 1;
			int left = 1;
			int right = 1;
			while (true) {
				left = arraystr.find('[', left);
				right = arraystr.find(']', right);
				if (left < right && left > 0 && right > 0) {
					left = arraystr.find('[', left + 1);
					right = arraystr.find(']', right + 1);
				}
				else {
					if (right == arraystr.size() - 1) {
						valuestr = arraystr.substr(0, right + 1);
						arr.JsonAddArrayStringToArray(valuestr);
						conti = false;
						break;
					}
					else {
						valuestr = arraystr.substr(0, right + 1);
						arraystr = arraystr.substr(right + 2, arraystr.size());
						arr.JsonAddArrayStringToArray(valuestr);
						break;
					}

				}
				last_left = left;
				last_right = right;
			}
		}
		else if (arraystr[0] == '{') {
			int last_left = 1;
			int last_right = 1;
			int left = 1;
			int right = 1;
			while (true) {
				left = arraystr.find('{', left);
				right = arraystr.find('}', right);
				if (left < right && left > 0 && right > 0) {
					left = arraystr.find('{', left + 1);
					right = arraystr.find('}', right + 1);
				}
				else {
					if (right == arraystr.size() - 1) {
						valuestr = arraystr.substr(0, right + 1);
						arr.JsonAddObjectStringToArray(valuestr);
						conti = false;
						break;
					}
					else {
						valuestr = arraystr.substr(0, right + 1);
						arraystr = arraystr.substr(right + 2, arraystr.size());
						arr.JsonAddObjectStringToArray(valuestr);
						break;
					}
				}
				last_left = left;
				last_right = right;
			}
		}
		else {
			valuelast = arraystr.find(',', 1);
			if (valuelast < 0) {
				valuelast = arraystr.size();
				valuestr = arraystr.substr(0, valuelast);
				if (IsDouble(valuestr)) {
					arr.JsonAddDoubleToArray(atof(valuestr.c_str()));
				}
				else if (valuestr == "true") {
					arr.JsonAddBoolToArray(true);
				}
				else if (valuestr == "false") {
					arr.JsonAddBoolToArray(false);
				}
				else {
					arr.JsonAddIntToArray(atoi(valuestr.c_str()));
				}
				break;
			}
			valuestr = arraystr.substr(valuefirst, valuelast - valuefirst);
			arraystr = arraystr.substr(valuelast + 1, arraystr.size());
			if (IsDouble(valuestr)) {
				arr.JsonAddDoubleToArray(atof(valuestr.c_str()));
			}
			else if (valuestr == "true") {
				arr.JsonAddBoolToArray(true);
			}
			else if (valuestr == "false") {
				arr.JsonAddBoolToArray(false);
			}
			else {
				arr.JsonAddIntToArray(atoi(valuestr.c_str()));
			}

		}
	}
	return arr;
}

int JsonArray::JsonGetArraySize() {
	return array.size();
}

int JsonArray::JsonGetIntFromArray(int index) {
	if (index < array.size())
		return atoi(array[index].c_str());
	else
		return -123456;
}

std::string JsonArray::JsonGetStringFromArray(int index) {
	if (index < array.size())
		return array[index];
	else
		return "-123456";
}

double JsonArray::JsonGetDoubleFromArray(int index) {
	if (index < array.size())
		return atof(array[index].c_str());
	else
		return -123456;
}

bool JsonArray::JsonGetBoolFromArray(int index) {
	if (index < array.size())
		if (array[index] == "true") {
			return true;
		}
		else {
			return false;
		}
	else
		return false;
}

JsonArray JsonArray::JsonGetArrayFromArray(int index) {
	JsonArray arr;
	if (index < array.size())
		return arr.JsonParseArray(array[index]);
	else
		return arr;
}

JsonObject JsonArray::JsonGetObjectFromArray(int index) {
	JsonObject obj;
	if (index < array.size())
		return obj.JsonParseObject(array[index]);
	else
		return obj;
}

std::string JsonArray::JsonGetArrayStringFromArray(int index) {
	if (index < array.size())
		return array[index];
	else
		return "-123456";
}

std::string JsonArray::JsonGetObjectStringFromArray(int index) {
	if (index < array.size())
		return array[index];
	else
		return "-123456";
}

void JsonArray::JsonDeleteArray() {
	array.clear();
	type.clear();
}

///////////////////////////////////////////////////////JsonObject//////////////////////////////////////////////////////////////
JsonObject::JsonObject() {

}

void JsonObject::JsonAddIntToObject(std::string key, int value) {
	obj_key.push_back(key);
	obj_value.push_back(ConvertToString(value));
	type.push_back(TypeInt);
}

void JsonObject::JsonAddStringToObject(std::string key, std::string value) {
	obj_key.push_back(key);
	obj_value.push_back(value);
	type.push_back(TypeString);
}

void JsonObject::JsonAddDoubleToObject(std::string key, double value) {
	obj_key.push_back(key);
	obj_value.push_back(ConvertToString(value));
	type.push_back(TypeDouble);
}

void JsonObject::JsonAddBoolToObject(std::string key, bool value) {
	obj_key.push_back(key);
	if (value) {
		obj_value.push_back("true");
	}
	else {
		obj_value.push_back("false");
	}
	type.push_back(TypeBool);
}

void JsonObject::JsonAddArrayStringToObject(std::string key, std::string value) {
	obj_key.push_back(key);
	obj_value.push_back(value);
	type.push_back(TypeArrayString);
}

void JsonObject::JsonAddObjectStringToObject(std::string key, std::string value) {
	obj_key.push_back(key);
	obj_value.push_back(value);
	type.push_back(TypeObjectString);
}

void JsonObject::JsonAddArrayToObject(std::string key, JsonArray arr) {
	obj_key.push_back(key);
	obj_value.push_back(arr.JsonPrintArray());
	type.push_back(TypeArray);
}

void JsonObject::JsonAddObjectToObject(std::string key, JsonObject obj) {
	obj_key.push_back(key);
	obj_value.push_back(obj.JsonPrintObject());
	type.push_back(TypeObject);
}

std::string JsonObject::JsonPrintObject() {
	std::string str;

	for (int i = 0; i < obj_value.size(); i++) {
		if (type[i] == TypeInt) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}
		else if (type[i] == TypeString) {
			str = str + '"' + obj_key[i] + '"' + ":" + '"' + obj_value[i] + '"';
		}
		else if (type[i] == TypeDouble) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}
		else if (type[i] == TypeBool) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}
		else if (type[i] == TypeArray) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}
		else if (type[i] == TypeObject) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}
		else if (type[i] == TypeArrayString) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}
		else if (type[i] == TypeObjectString) {
			str = str + '"' + obj_key[i] + '"' + ":" + obj_value[i];
		}

		if (i < obj_value.size() - 1) {
			str += ',';
		}
	}
	str = "{" + str + "}";
	return str;
}

JsonObject JsonObject::JsonParseObject(std::string objstr) {
	JsonObject obj;
	objstr = objstr.substr(1, objstr.size() - 2);
	int keyfirst = 0;
	int keylast = 0;
	std::string keystr;
	int valuefirst = 0;
	int valuelast = 0;
	std::string valuestr;
	bool conti = true;
	while (conti) {
		keyfirst = objstr.find('"', 0);
		keylast = objstr.find('"', keyfirst + 1);
		keystr = objstr.substr(keyfirst + 1, keylast - keyfirst - 1);
		objstr = objstr.substr(keylast + 2, objstr.size() - keylast - 2);

		if (objstr[0] == '"') {
			valuelast = objstr.find('"', 1);
			if (valuelast == objstr.size() - 1) {
				valuelast = objstr.size();
				valuestr = objstr.substr(1, valuelast - 2);
				obj.JsonAddStringToObject(keystr, valuestr);
				break;
			}
			valuestr = objstr.substr(valuefirst + 1, valuelast - valuefirst - 1);
			objstr = objstr.substr(valuelast + 2, objstr.size());
			obj.JsonAddStringToObject(keystr, valuestr);
		}
		else if (objstr[0] == '[') {
			int last_left = 1;
			int last_right = 1;
			int left = 1;
			int right = 1;
			while (true) {
				left = objstr.find('[', left);
				right = objstr.find(']', right);
				if (left < right && left > 0 && right > 0) {
					left = objstr.find('[', left + 1);
					right = objstr.find(']', right + 1);
				}
				else {
					if (right == objstr.size() - 1) {
						valuestr = objstr.substr(0, right + 1);
						obj.JsonAddArrayStringToObject(keystr, valuestr);
						conti = false;
						break;
					}
					else {
						valuestr = objstr.substr(0, right + 1);
						objstr = objstr.substr(right + 2, objstr.size());
						obj.JsonAddArrayStringToObject(keystr, valuestr);
						break;
					}

				}
				last_left = left;
				last_right = right;
			}
		}
		else if (objstr[0] == '{') {
			int last_left = 1;
			int last_right = 1;
			int left = 1;
			int right = 1;
			while (true) {
				left = objstr.find('{', left);
				right = objstr.find('}', right);
				if (left < right && left > 0 && right > 0) {
					left = objstr.find('{', left + 1);
					right = objstr.find('}', right + 1);
				}
				else {
					if (right == objstr.size() - 1) {
						valuestr = objstr.substr(0, right + 1);
						obj.JsonAddObjectStringToObject(keystr, valuestr);
						conti = false;
						break;
					}
					else {
						valuestr = objstr.substr(0, right + 1);
						objstr = objstr.substr(right + 2, objstr.size());
						obj.JsonAddObjectStringToObject(keystr, valuestr);
						break;
					}

				}
				last_left = left;
				last_right = right;
			}
		}
		else {
			valuelast = objstr.find(',', 1);
			if (valuelast < 0) {
				valuelast = objstr.size();
				valuestr = objstr.substr(0, valuelast);

				if (IsDouble(valuestr)) {
					obj.JsonAddDoubleToObject(keystr, atof(valuestr.c_str()));
				}
				else if (valuestr == "true") {
					obj.JsonAddBoolToObject(keystr, true);
				}
				else if (valuestr == "false") {
					obj.JsonAddBoolToObject(keystr, false);
				}
				else {
					obj.JsonAddIntToObject(keystr, atoi(valuestr.c_str()));
				}
				break;
			}
			valuestr = objstr.substr(valuefirst, valuelast - valuefirst);
			objstr = objstr.substr(valuelast + 1, objstr.size());
			if (IsDouble(valuestr)) {
				obj.JsonAddDoubleToObject(keystr, atof(valuestr.c_str()));
			}
			else if (valuestr == "true") {
				obj.JsonAddBoolToObject(keystr, true);
			}
			else if (valuestr == "false") {
				obj.JsonAddBoolToObject(keystr, false);
			}
			else {
				obj.JsonAddIntToObject(keystr, atoi(valuestr.c_str()));
			}
		}
	}
	return obj;
}

int JsonObject::JsonGetIntFromObject(std::string key) {
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return atoi(obj_value[i].c_str());
	}
	return -123456;

}

std::string JsonObject::JsonGetStringFromObject(std::string key) {
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return obj_value[i];
	}
	return "-123456";
}

double JsonObject::JsonGetDoubleFromObject(std::string key) {
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return atof(obj_value[i].c_str());
	}
	return -123456;

}

bool JsonObject::JsonGetBoolFromObject(std::string key) {

	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key) {
			if (obj_value[i] == "true") {
				return true;
			}
		}
	}
	return false;
}

JsonArray JsonObject::JsonGetArrayFromObject(std::string key) {
	JsonArray arr;
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return arr.JsonParseArray(obj_value[i]);
	}
	return arr;
}
JsonObject JsonObject::JsonGetObjectFromObject(std::string key) {
	JsonObject obj;
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return obj.JsonParseObject(obj_value[i]);
	}
	return obj;
}

std::string JsonObject::JsonGetArrayStringFromObject(std::string key) {
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return obj_value[i];
	}
	return "-123456";
}

std::string JsonObject::JsonGetObjectStringFromObject(std::string key) {
	for (int i = 0; i < obj_key.size(); i++) {
		if (obj_key[i] == key)
			return obj_value[i];
	}
	return "-123456";
}

void JsonObject::JsonDeleteObject() {
	obj_key.clear();
	obj_value.clear();
	type.clear();
}