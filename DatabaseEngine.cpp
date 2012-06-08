/******************************** 
 * Laramie Goode				*
 * CSCE-315-Project_1			*
 * Database Engine (WIP)		*
 ********************************/

#include "stdlib.h" 
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

void wait() {
	char a;
	cin >> a;
}

string intToString(int number) {
	stringstream ss;
	ss << number;
	return ss.str();
}

class dataType {

	bool _isInt;
	int length;
	
public:

	dataType() {}

	/*
	dataType(bool isInt) {
		_isInt = isInt;
	}*/
	
	dataType(bool isInt, int size = 0) {
		_isInt = isInt;
		length = size;
	}

	dataType(int size) {
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

class Attribute {

public:

	dataType type;
	string name;
	vector<string> cells;

	Attribute(string input_name) {
		name = input_name;
	}
	
	Attribute(string input_name, dataType inputType) {
		name = input_name;
		type = inputType;
	}
	
	//Probably a rare case use of this constructor
	Attribute(string input_name, dataType input_type, vector<string> input_cells) {
		name = input_name;
		type = input_type;
		cells = input_cells;
	}
	
	string getName() {
		return name;
	}
	
	void setName(string input_name) {
		name = input_name;
	}
	
	void addCell(string value) {
		cells.push_back(value);
	}
	
	int findCellIndex(string value) {
	
		int i = 0;
		while( strcmp(cells[i].c_str(), value.c_str()) != 0)  {
			i++;
		}
		
		if(i < cells.size()) {
			return i;
		} else {
			cout << "Error in findCellIndex, i is " << i << ", exiting program\n";
			exit(1);
			return -1;
			//error value, watch out for vector[-1] results
		}
	}
	
	string getElement(int index) {
		return cells[index];
	}
	
	void setElement(int spot, string value) {
		cells[spot] = value;
	}
	
	int getSize() {
		return cells.size();
	}
	
	bool hasRepeats() {
		bool repeat = false;
		for(int i = 0; i < cells.size(); i++) {
			for(int j = 0; j < cells.size(); j++) {
				if(i != j && strcmp(cells[i].c_str(), cells[j].c_str()) == 0) {
					repeat = true;
				}				
			}
		}
		return repeat;
	}
	
	void setElementByName(string old_value, string new_value) {
		cells[findCellIndex(old_value)] = new_value;
	}

	string getType() {
		return type.getType();
	}

	bool isInt() {
		return type.isInt();
	}
	
	void print() {
		cout << "Name:\t" << name << '\t' << "Datatype:\t" << getType() << '\n';
	}

};

class Relation {

public:

	//map<string, Attribute*> foo;

	string name;
	map<string, Attribute> columns;
	map<string, Attribute>::iterator start;
	int primaryKey;

	Relation(string input_name) {
		name = input_name;
	}
	
	Relation(string input_name, vector<string> input) {
		//wip
	}
	
	bool isUniqueColumn(Attribute column) {
		return true;  //wip
	}
	
	
	void addAttribute(string name) {
		Attribute attr(name);
		columns.insert( pair<string,Attribute>(name, attr) );
	}
	
	void addAttribute(string name, dataType type) {
		Attribute attr(name, type);
		columns.insert( pair<string,Attribute>(name, attr) );
	}
	
	void deleteAttribute(string name) {
		columns.erase(name);
	}

	void addTuple(vector<string> input) {
		int i = 0;
		for(map<string, Attribute>::iterator iter = columns.begin(); iter != columns.end(); iter++) {
			(*iter).second.cells.push_back(input[i]);
			i++;
		}
	}
	
	Attribute findAttribute(string input_name) {
		map<string, Attribute>::iterator iter = columns.begin();
		while( strcmp( (*iter).second.name.c_str(), input_name.c_str()) != 0 && iter != columns.end()) {
			iter++;
		}
		return (*iter).second;
	}
	
	void setElement(int x, int y, string value) {
	
		map<string, Attribute>::iterator iter = columns.begin();
		for(int i = 0; i < x; i++) {
			iter++;
		}
		(*iter).second.setElement(y, value);
	}
	
	string getElement(int x, int y) {
	
		map<string, Attribute>::iterator iter = columns.begin();
		for(int i = 0; i < x; i++) {
			iter++;
		}
		return (*iter).second.cells[y];	
	}
	
	string getName() {
		return name;
	}
	
	string stringify() {
		string table = "(";
		int j = 0;	
		for(map<string, Attribute>::iterator iter = columns.begin(); iter != columns.end(); iter++) {
			j++;
			if( j == columns.size() ) {
				table = table + (*iter).second.getName() + " " + (*iter).second.getType() + ")\n";
			} else {
				table = table + (*iter).second.getName() + " " + (*iter).second.getType() + ", ";
			}
		}
	
		start = columns.begin();
		for(int i = 0; i < (*start).second.getSize(); i++) {
			table = table + "(";	
			j = 0;
			for(map<string, Attribute>::iterator iter = columns.begin(); iter != columns.end(); iter++) {
				if(j == (*start).second.getSize()) {
					if( (*iter).second.isInt() ) {
						table = table + (*iter).second.getElement(i) + ")\n";
					} else {
						table = table + "\"" + (*iter).second.getElement(i) + "\")\n";
					}
				} else {
					if( (*iter).second.isInt() ) {
						table = table + (*iter).second.getElement(i) + ", ";
					} else {
						table = table + "\"" + (*iter).second.getElement(i) + "\", ";
					}
				}	
				j++;
			}
		}
		table = table + "\n";
		
		return table;
		//Idea behind this is to convert the relation into a string
		//The string can then be written to a file
	}
	
	
	
	void print() {
		
		//Prints the header (name of attributes)
		cout << '\t';
		for(map<string, Attribute>::iterator iter = columns.begin(); iter != columns.end(); iter++) {
				cout << (*iter).second.getName() << '\t';
		}
		cout << '\n';
		
		//Prints values of elements
		start = columns.begin();
		for(int i = 0; i < (*start).second.getSize(); i++) {
			cout << i << '\t';
			for(map<string, Attribute>::iterator iter = columns.begin(); iter != columns.end(); iter++) {
				cout << (*iter).second.getElement(i) << '\t';
			}
			cout << '\n';
		}
		cout << '\n';
	}
};

class Domain {
	//halp
};

class Value {
	//halp
};

template <class DB_type>
void writeToFile(DB_type writeFrom) {
	string filename = writeFrom.getName();
	filename = filename + ".db";
	
	ofstream outputFile;
	outputFile.open(filename.c_str());
	outputFile << writeFrom.stringify();
	outputFile.close();
	
}

bool isNum(char input) {
	if(input == '-' || input == '0' ||
	   input == '1' || input == '2' ||
	   input == '3' || input == '4' ||
	   input == '5' || input == '6' ||
	   input == '7' || input == '8' ||
	   input == '9' ) {
		return true;
	} else {
		return false;
	}
}


void parseHeader(string line, Relation table) {
	//dataType type;	
	string temp = "";
	string name = "";
	string varCharLength = "";
	
	for(int i = 0; i < line.size(); i++) {
		if( isalpha(line[i]) ) {
			while( isalpha(line[i]) ) {
				name = name + line[i];
				i++;
			}
			//
			
			i++;
			while( isalpha(line[i]) ) {
				temp = temp + line[i];
				i++;
			}
			
			if( strcmp(temp.c_str(), "INTEGER") == 0) {
				dataType type(true);
				//Attribute attr(name, type);
				table.addAttribute(name, type);
				//attr.print();
			} else {
				if( strcmp (temp.c_str(), "VARCHAR") == 0 ) {
					i++;
					while( isNum(line[i]) ) {
						varCharLength = varCharLength + line[i];
						i++;
					}
					//
					dataType type(atoi(varCharLength.c_str()));
					//Attribute attr(name, type);
					table.addAttribute(name, type);
					//attr.print();
				} else { cout << "ERROR IN PARSING\n"; }
			}
			
			//Attribute attr(name, type);
			//attr.print();
			temp = "";
		}
		i = i++;
		name = "";
		varCharLength = "";
	}
}

void parseTuples(string line, Relation table) {
	string temp = "";
	for(int i = 0; i < line.size(); i++) {
		if( line[i] == '\"' ) {
			i++;
			while(line[i] != '\"' ) {
				temp = temp + line[i];
				i++;
			}
			//cout << "VARCHAR -> " << temp << '\n';
			
			temp = "";
		} else {
			if( isNum(line[i]) ) {
				while(isNum(line[i])) {
					temp = temp + line[i];
					i++;
				}
				//cout << "INTEGER -> " << temp << '\n';
				
				temp = "";
			}
		}
		if(line[i] == ')') {
			break;
		}
	}
}

Relation readFromFile(string input) {

	ifstream inputFile;
	inputFile.open(input.c_str());
	
	//copy relation from .db file to memory (incomplete)
	Relation importedRelation(input);
	
	char currentChar;
	vector<string> parsedInfo;
	string line;

	getline(inputFile, line);
	parseHeader(line, importedRelation);
	
	while(inputFile.good()) {
		getline(inputFile, line);
		parseTuples(line, importedRelation);
	}
	
	inputFile.close();
	
	return importedRelation;
}



int main() {

	Relation table = readFromFile("test.db");

	dataType charType(false, 20);
	dataType intType(true);

	//cout << table.columns.size(); 
	
	
	//table.addAttribute("First", charType);
	//table.addAttribute("Second", intType);
	//table.addAttribute("Third", charType);
	
	vector<string> input(3);
	input[0] = "hello";
	input[1] = "343";
	input[2] = "dog";
	
	vector<string> input2(3);
	input2[0] = "bye";
	input2[1] = "404";
	input2[2] = "cat";

	//table.addTuple(input);
	
	//table.addTuple(input2);
	
	//table.setElement(0, 1, "NEW");
	
	table.print();
	
	//cout << table.stringify();
	
	writeToFile<Relation>(table);
	
	string testTuples = "(\"hello\", \"there\", 324)"; 
	string testHeader = "First VARCHAR(20), Second INTEGER, Third VARCHAR(20))";
	
	//parseTuples(testTuples, table);
	
	parseHeader(testHeader, table);
	
	//table.deleteAttribute("Second");
	
	//table.print();

	return 0;
}
