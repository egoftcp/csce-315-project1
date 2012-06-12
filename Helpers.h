#ifndef HELPERS_H
#define HELPERS_H

#include <sstream>
#include <string>

namespace Helpers{

using namespace std;


	string retUpper(string inStr){
			string upp = inStr;
			for(string::iterator it = upp.begin(); it!=upp.end(); ++it){
				*it = toupper((unsigned char)(*it));
			}
			return upp;
	}


	bool isNum(char input) {
		if(input == '-' || input == '0' ||
		   input == '1' || input == '2' ||
		   input == '3' || input == '4' ||
		   input == '5' || input == '6' ||
		   input == '7' || input == '8' ||
		   input == '9' ) {
			return true;
		}
		else {
			return false;
		}
	}
	
	
	int stringToInt(string str){
	int i;
	stringstream ss(str);
	ss >> i;
	return i;
}



}


#endif


