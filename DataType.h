#ifndef DATATYPE_H
#define DATATYPE_H

#include <string>

using namespace std;

//TODO: extrapolate definitions to .cpp 



string intToString(int number) {
	stringstream ss;
	ss << number;
	return ss.str();
}



class DataType {
	bool _isInt;
	int length;
	
public:
	DataType() {}
	DataType(bool isInt, int size = 0) {
		_isInt = isInt;
		length = size;
	}

	DataType(int size) {
		length = size;
		_isInt = false;
	}

	bool isInt() {
		return _isInt;
	}
	
	int size() {
		return length;
	}

	string getType() {
		if(_isInt) {
			return "INTEGER";
		} else {
			return "VARCHAR(" + intToString(length) + ")";
		}
	}
};

#endif



