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
#include "Parser.h"
#include <queue>

using namespace std;

void close() {
	exit(0);
}

void wait() {
	char a;
	cin >> a;
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

void parseArguments(string input) {
	

}

string intToString(int number) {
	stringstream ss;
	ss << number;
	return ss.str();
}

int stringToInt(string str){
	int i;
	stringstream ss(str);
	ss>>i;
	return i;
}

class dataType {

	bool _isInt;
	int length;
	
public:

	dataType() {}
	
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

	Attribute() {}
	
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

	vector<string> primaryKeys; //attribute names


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
	
	void addAttribute(string name, dataType type) {
		Attribute attr(name, type);
		pair< map<string,Attribute>::iterator, bool > ret;
		ret = columns.insert( pair<string,Attribute>(name, attr) );
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
	
	Relation selection(string input) {
		Relation result("a");
		
		return result;
	}
	
	Relation projection(string input) {
		Relation result("b");
		
		return result;
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
	
	void parseHeader(string line) {
		string temp = "";
		string name = "";
		string varCharLength = "";
	
		for(int i = 0; i < line.size(); i++) {
			if( isalpha(line[i]) ) {
				while( isalpha(line[i]) ) {
					name = name + line[i];
					i++;
				}

				i++;
				while( isalpha(line[i]) ) {
					temp = temp + line[i];
					i++;
				}
			
				if( strcmp(temp.c_str(), "INTEGER") == 0) {
					dataType type(true);
					addAttribute(name, type);
				} else {
					if( strcmp (temp.c_str(), "VARCHAR") == 0 ) {
						i++;
						while( isNum(line[i]) ) {
							varCharLength = varCharLength + line[i];
							i++;
						}
						dataType type(atoi(varCharLength.c_str()));
						addAttribute(name, type);
					} else { cout << '[' + i + "] " "ERROR IN PARSING\n"; }
				}
				temp = "";
			}
			i = i++;
			name = "";
			varCharLength = "";
		}
	}
	
	void parseTuples(string line) {
		vector<string> cells;
		string temp = "";
		for(int i = 0; i < line.size(); i++) {
			if( line[i] == '\"' ) {
				i++;
				while(line[i] != '\"' ) {
					temp = temp + line[i];
					i++;
				}
				cells.push_back(temp);
				temp = "";
			} else {
				if( isNum(line[i]) ) {
					while(isNum(line[i])) {
						temp = temp + line[i];
						i++;
					}
					cells.push_back(temp);				
					temp = "";
				}
			}
			if(line[i] == ')') {
				break;
			}
		}
		
		if(cells.size() != 0) {
			addTuple(cells);
		}
	}
	
	int getHeight() {
		map<string, Attribute>::iterator iter4size = columns.begin();
		return ((*iter4size).second.getSize());
	}
	
	Relation Relation::operator+(const Relation& right) {
		Relation result = *this;
		bool equal; 
		map<string, Attribute>::iterator iter1 = result.columns.begin();
			
	//} else {	
	}
	
	void selection(Relation table, string input) {
		
		
	}
	
	void projection(Relation table, string input) {
	
		
	
	}
	
	void crossProduct(Relation table1, Relation table2) {
		for(map<string, Attribute>::iterator iter = table1.columns.begin(); iter != table1.columns.end(); iter++) {
			addAttribute((*iter).second.getName(), (*iter).second.type);
		}
		for(map<string, Attribute>::iterator iter = table2.columns.begin(); iter != table2.columns.end(); iter++) {
			addAttribute((*iter).second.getName(), (*iter).second.type);
		}
		
		vector<string> first;
		vector<string> second;
		vector<string> data;
	
			for(int i = 0; i < table1.getHeight(); i++) {
				
				for(map<string, Attribute>::iterator iter = table1.columns.begin(); iter != table1.columns.end(); iter++) {
					first.push_back(((*iter).second.cells[i]));
					cout << ((*iter).second.cells[i]) << '\t';	
					for(int j = 0; j < table2.getHeight(); j++) {
						for(map<string, Attribute>::iterator iter2 = table2.columns.begin(); iter2 != table2.columns.end(); iter2++) {
							second.push_back(((*iter2).second.cells[j]));
							cout << ((*iter).second.cells[i]) << '\t';
						}
						
						/*
						for(int k = 0; k < first.size(); k++) {
							data.push_back(first[k]);
						}
						for(int k = 0; k < second.size(); k++) {
							data.push_back(second[k]);
						}*/
						
						second.clear();
					}
					cout << '\n';
					first.clear();
				}
				
				for(int j = 0; j < data.size(); j++) {
					cout << data[j] << '\t';
				}
				cout << '\n';
				
				data.clear();
			}
			//addTuple(data);			
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

Relation readFromFile(string input) {

	ifstream inputFile;
	inputFile.open(input.c_str());
	
	string name = input.substr(0, input.size()-3);
	
	Relation importedRelation(name);
	
	char currentChar;
	vector<string> parsedInfo;
	string line;

	getline(inputFile, line);
	importedRelation.parseHeader(line);
	
	while(!inputFile.eof()) {
		getline(inputFile, line);
		importedRelation.parseTuples(line);
	}
	
	inputFile.close();
	
	return importedRelation;
}

int main() {

	Relation importedTable = readFromFile("test.db");
	Relation table("foo");
	
	Relation crossTable("cross");
	
	dataType charType(false, 20);
	dataType intType(true);
	
	table.addAttribute("FOO", charType);
	table.addAttribute("REDDIT", charType);
	table.addAttribute("BAR", charType);
	
	vector<string> input(3);
	input[0] = "MINE";
	input[1] = "SPLIN";
	input[2] = "HALO";
	
	vector<string> input2(3);
	input2[0] = "DIABLO";
	input2[1] = "SC2";
	input2[2] = "HL1";

	table.addTuple(input);
	table.addTuple(input2);
	
	crossTable.crossProduct(table, importedTable);
	
	//crossTable.print();
	
	//importedTable.print();
	
	//writeToFile<Relation>(table);
	
	//table.deleteAttribute("Second");
	
	//table.print();

	return 0;
}




map<string,Relation*> relsInMem;	//need to release memory on exit



string ExecuteCommand(string Command){
	//Create Parser Instance with Debug=0; (no output, silent)
	Parser parserInst(0); //This should only be instanciated/constructed once, but this will work for now..
	int fails = parserInst.ParseProgramBlock(Command);
	if(fails!=0){
		return "Input is not syntactically correct, returning"; 
	}
	
	int tI=0;
	
	vector<string> toks = parserInst.getTokens(Command);
	if(toks[tI] == "CREATE"){
		string relName = toks[2];
		queue<string> attrNames;
		queue<int> attrTypes;
		//typed-attribute-list will always start at index=4 (but open paren @ 3) and end when a close-paren follows a data type (instead of a comma)
		int alI=3; //attribute-list-Index (alI)
		do{
			alI++;
			attrNames.push(toks[alI]);
			alI++;
			string typeName = toks[alI];
			if(typeName=="VARCHAR"){
				//cout<<"VC"<<endl;
				alI+=2;
				int len = stringToInt(toks[alI]);
				//cout<<len<<endl;
				attrTypes.push(len);
				alI+=2;			
			}else if(typeName=="INTEGER"){
				attrTypes.push(0);
				alI++;
			}else{
				cerr<<"Something terrible happened in ExecuteCommand-Create-TypedAttributeList\n";
			}
		}while(toks[alI]==",");
		alI+=3; //move index to open-paren of 'primary key' attribute-list
		queue<string> pkNames;
		do{
			alI++;
			pkNames.push(toks[alI]);
			alI++;
			
		}while(toks[alI]==",");
		

		Relation* newRel = new Relation(relName);
		
		while(!attrNames.empty()){
			dataType dt((attrTypes.front()==0?true:false),attrTypes.front());
			
			newRel->addAttribute(attrNames.front(),dt);
			attrNames.pop();
			attrTypes.pop();
			
		}
		while(!pkNames.empty()){
			newRel->primaryKeys.push_back(pkNames.front());
			pkNames.pop();
		}
		
		relsInMem.insert( pair<string,Relation*>(relName,newRel) );
		
		string crRel = relsInMem[relName]->stringify();
		return crRel;
	}
	else if(toks[tI] == "INSERT"){
		string relName = toks[2];
		vector<string> vals;
		int intInd=5;
		do{
			intInd++;
			if(toks[intInd]=="\""){
				intInd++;
				vals.push_back(toks[intInd]);
				intInd+=2;
			}else if(toks[intInd]=="-"){
				intInd++;
				vals.push_back("-"+toks[intInd]);
				intInd++;
			}else{
				vals.push_back(toks[intInd]);
				intInd++;
			}
		}while(toks[intInd]==",");
		relsInMem[relName]->addTuple(vals);
		return relsInMem[relName]->stringify();
	}
	
	
	
	return "NULLL";
}



int main()2{
	
	cout<<"trying create:"<<endl;
	string res = ExecuteCommand("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
	relsInMem["animals"]->print();
	cout<<"trying insert:"<<endl;
	res = ExecuteCommand("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
	relsInMem["animals"]->print();
	
	
	
	cout<<"Freeing Memory:\n";
	cout<<"--Relations:\n";
	for( map<string,Relation*>::iterator relIt= relsInMem.begin(); relIt != relsInMem.end(); ++relIt){
		cout<<(*relIt).first<<" @ "<<relIt->second<<endl;
		delete relIt->second;
	}
	//cout<<"--Relations:";
	
	cout << "Press ENTER to continue";
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	

	return 0;
}





