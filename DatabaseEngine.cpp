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

class Attribute {

	string name;
	vector<string> cells;
	
public:

	Attribute(string input_name) {
		name = input_name;
	}
	
	string* getName() {
		return &name;
	}
	
	void addCell(string value) {
		cells.push_back(value);
	}
	
	int getCellIndex(string value) {
	
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
	
	void setCell(string old_value, string new_value) {
		cells[getCellIndex(old_value)] = new_value;
	}
	
};

class Tuple {
	
	//vector<string*> cells;
	//Gonna try and have these cells point to the ones inside the attributes vector
	//Should cause updates/changes to be smoother
	
public:

	vector<string*> cells;

	void add(Attribute* attr) {
		cells.push_back( attr->getName() );
	}
	
	int getCellIndex(string value) {
		//copy-pasted from attribute, might just inherit these from the same place
	
		int i = 0;
				
		while( strcmp(((string*)cells[i])->c_str(), value.c_str()) != 0 && i < cells.size())  {
			i++;
		}
	
		if(i < cells.size()) {
			return i;
		} else {
			return -1;
			//error value, watch out for vector[-1] results
		}
	}
	
};

class Relation {

	string name;
	map<string, Attribute> columns;
	vector<Tuple> rows;
	
public:

	Relation(string input_name) {
		name = input_name;
	}
	
	void addAttribute(string name) {
	
		Attribute attr(name);
		columns.insert( pair<string,Attribute>(name, attr) );
		
		//columns[name]
	
	}
	
	void deleteAttribute(string name) {
	
		//deletes the cell pointer in every row inside the row vector
		for(int i = 0; i < rows.size(); i++) {
			rows[i].cells.erase(rows[i].cells.begin()+rows[i].getCellIndex(name));
		}
	
		//deltes the named column
		columns.erase(name);
	
	}
	
	void addTuple(Tuple row) {
		
	}

	string getName() {
		return name;
	}
	
	string stringify() {
	
		return "0";
		//Idea behind this is to convert the relation into a string
		//The string can then be written to a file
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

	return 0;
}
