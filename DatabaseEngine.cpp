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

using namespace std;

enum dataType { VARCHAR, INTEGER, DATE };

class myDataTypes {
};

class varChar {
public:
	varChar(int size) {
	}
};

class Attribute {

public:

	//dataType type;
	string name;
	string type;
	vector<string> cells;

	Attribute(string input_name) {
		name = input_name;
		type = "NULL";
	}
	
	Attribute(string input_name, string input_type) {
		name = input_name;
		type = input_type;
	}
	
	//Probably a rare case use of this constructor
	Attribute(string input_name, string input_type, vector<string> input_cells) {
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
	
	void setElementByName(string old_value, string new_value) {
		cells[findCellIndex(old_value)] = new_value;
	}
};

class Tuple {
public:
};

class Relation {

public:

	string name;
	map<string, Attribute> columns;
	map<string, Attribute>::iterator start;
	int primaryKey;

	Relation(string input_name) {
		name = input_name;
	}
	
	void addAttribute(string name) {
		Attribute attr(name);
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
	
	string stringify() { //Incomplete
	
		return "0";
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

	ofstream outputFile;
	outputFile.open(writeFrom.getName() + ".db");
	outputFile << writeFrom.stringify();
	outputFile.close();
	
}

void readFromFile(string input) {

	ifstream inputFile;
	inputFile.open(input.c_str());
	
	//copy relation from .db file to memory (incomplete)
	Relation importedRelation(input);
	
	inputFile.close();
	
}

int main() {

	Relation table("test");
	table.addAttribute("First");
	table.addAttribute("Second");
	table.addAttribute("Third");
	
	vector<string> input(3);
	input[0] = "hello";
	input[1] = "dog";
	input[2] = "343";
	
	vector<string> input2(3);
	input2[0] = "bye";
	input2[1] = "cat";
	input2[2] = "404";

	table.addTuple(input);
	
	table.print();

	table.addTuple(input2);
	
	table.print();
	
	table.setElement(0, 1, "NEW");
	
	table.print();
	
	cout << table.getElement(0,1);
	
	//table.deleteAttribute("Second");
	
	//table.print();

	return 0;
}
