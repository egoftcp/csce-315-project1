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
	ss >> i;
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
		for(vector<string>::iterator iter = cells.begin(); iter != find(cells.begin(), cells.end(), value); iter++) {
			i++;
		}
		return i;
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
					return repeat;
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

	string name;
	vector<string> primaryKeys; //attribute names
	//vector<string> values;
	vector<Attribute> columns;
	map<string, int> indices;
	//map<string, Attribute>::iterator start;
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
		columns.push_back(attr);
		indices[name] = (columns.size() - 1);
	}

	void addSeveralAttributes(vector<string> name, vector<dataType> type) {
		for(int i = 0; i < name.size(); i++) {
			addAttribute(name[i], type[i]);
		}
	}
	
	void deleteAttribute(string name) {
		vector<Attribute>::iterator iter = columns.begin();

		columns.erase((iter + indices[name]));
		indices.erase(name);
	}

	void addTuple(vector<string> input) {
		int j = 0;
		for(int i = 0; i < columns.size(); i++) {
			columns[i].cells.push_back(input[j]);
			j++;
		}
	}

	vector<string> getTuple(int index) {
		vector<string> output;
		for(int i = 0; i < columns.size(); i++) {
			output.push_back(columns[i].cells[index]);
		}
		return output;
	}
	
	Attribute findAttribute(string input_name) {
		return columns[indices[input_name]];
	}
	
	void setElement(int x, int y, string value) {
		columns[x].cells[y] = value;
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
		for(int i = 0; i < columns.size(); i++) {
			j++;
			if( j == columns.size() ) {
				table = table + columns[i].getName() + " " + columns[i].getType() + ")\n";
			} else {
				table = table + columns[i].getName() + " " + columns[i].getType() + ", ";
			}
		}
	
		for(int i = 0; i < columns[0].getSize(); i++) {
			table = table + "(";	
			j = 0;
			for(int k = 0; k < columns.size(); k++) {
				if(j == columns[0].getSize()) {
					if( columns[k].isInt() ) {
						table = table + columns[k].getElement(i) + ")\n";
					} else {
						table = table + "\"" + columns[k].getElement(i) + "\")\n";
					}
				} else {
					if( columns[k].isInt() ) {
						table = table + columns[k].getElement(i) + ", ";
					} else {
						table = table + "\"" + columns[k].getElement(i) + "\", ";
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
		for(int i = 0; i < columns.size(); i++) {
			cout << columns[i].getName() << '\t';
		}
		cout << '\n';

		for(int i = 0; i < columns[0].cells.size(); i++) {
			for(int j = 0; j < columns.size(); j++) {
				cout << columns[j].cells[i] << '\t';
			}
			cout << '\n';
		}
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
			//i = i++;
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
		return (columns[0].getSize());
	}
	
	Relation Relation::operator+(const Relation& right) {
		Relation result = *this;
		bool equal; 	
	}
	
	void selection(Relation table, string input) {
		
	}
	
	void projection(Relation table, string input) {
		
	}
	
	void crossProduct(Relation table1, Relation table2) {
		vector<string> names;
		vector<dataType> types;
		
		for(int i = 0; i < table1.columns.size(); i++) {
			names.push_back( table1.columns[i].getName() );
			types.push_back( table1.columns[i].type );
		}
		for(int i = 0; i < table2.columns.size(); i++) {
			names.push_back( table2.columns[i].getName() );
			types.push_back( table2.columns[i].type );
		}
		addSeveralAttributes(names, types);

		vector<string> first;
		vector<string> second;
		vector<string> data;

		for(int i = 0; i < table1.getHeight(); i++) {

			for(int j = 0; j < table2.getHeight(); j++) {
				first = table1.getTuple(i);
				second = table2.getTuple(j);

				for(int m = 0; m < first.size(); m++) {
					data.push_back(first[m]);
				}

				for(int k = 0; k < second.size(); k++) {
					data.push_back(second[k]);
				}
				
				addTuple(data);
				data.clear();
				first.clear();
				second.clear();
			}
		}
	}
	
		void deleteTuple(int index) {
		
		for(int i = 0; i < columns.size(); i++) {
			vector<string>::iterator iter = columns[i].cells.begin() + index;
			columns[i].cells.erase(iter);		
		}
	}

	bool matchingAttributes(Relation table1, Relation table2) {
	
		if(table1.columns.size() == table2.columns.size()) {
			bool hasMatch;


			for(int i = 0; i < table1.columns.size(); i++) {
				hasMatch = false;
				for(int j = 0; j < table2.columns.size(); j++) {
					if(strcmp(table1.columns[i].getName().c_str(), table2.columns[j].getName().c_str()) == 0) {
						hasMatch = true;
					}
				}
				if(hasMatch == false) {
					return false;
				}
			}

			return true;

		} else {
			return false;
		}
	
		//return true;
	}

	vector<string> constructTupleFromIndex(int index) {
		vector<string> tuple;
		for(int i = 0; i < columns.size(); i++) {
			tuple.push_back(columns[i].cells[index]);
		}
		
		/*
		cout << "***constructTupleFromIndex***\n";
		for(int i = 0; i < tuple.size(); i++) {
			cout << tuple[i] << '\t';
		}
		cout << "\n========================\n";*/
		
		return tuple;
	}

	bool equalTuples(vector<string> tuple1, vector<string> tuple2) {
		if(tuple1.size() == tuple2.size()) {
			bool hasMatch;
			for(int i = 0; i < tuple1.size(); i++) {
				hasMatch = false;
				for(int j = 0; j < tuple2.size(); j++) {
					if(strcmp(tuple1[i].c_str(), tuple2[j].c_str()) == 0) {
						hasMatch = true;
					}
				}

				if(hasMatch == false) {
					return false;
				}

			}

			return true;

		} else {
			return false;
		}
	}
	
	int tableUnion(Relation table1, Relation table2) {
		if(!matchingAttributes(table1, table2)) {
			cout << "Incompatible tables for Union operation\n";
			return -1;
		} else {

			for(int i = 0; i < table1.getHeight(); i++) {
				addTuple(table1.constructTupleFromIndex(i));
			}
			
			bool alreadyInTable1;
			int index;

			for(int i = 0; i < table2.getHeight(); i++) {
				alreadyInTable1 = false;
				for(int j = 0; j < table1.getHeight(); j++) {

					if(equalTuples(table2.constructTupleFromIndex(i), table1.constructTupleFromIndex(j))) {
						alreadyInTable1 = true;
					}

				}

				if(alreadyInTable1) {
					//do nothing
				} else {
					addTuple(table2.constructTupleFromIndex(i));
				}
			}
		}
		return 0;
	}

	int tableDifference(Relation table1, Relation table2) {
		//table1 - table2

		if(!matchingAttributes(table1, table2)) {
			cout << "Incompatible tables for Difference operation\n";
			return -1;
		} else {


			for(int i = 0; i < table1.getHeight(); i++) {

				for(int j = 0; j < table2.getHeight(); j++) {

					if(equalTuples(table1.constructTupleFromIndex(i), table2.constructTupleFromIndex(j))) {
						deleteTuple(i);
					}
				}
			}
		}
	}

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


Relation* readFromFilePtr(string input) {
	ifstream inputFile;
	inputFile.open(input.c_str());
	
	string name = input.substr(0, input.size()-3);
	
	Relation* importedRelation= new Relation(name);
	
	char currentChar;
	vector<string> parsedInfo;
	string line;

	getline(inputFile, line);
	importedRelation->parseHeader(line);
	
	while(!inputFile.eof()) {
		getline(inputFile, line);
		importedRelation->parseTuples(line);
	}
	
	inputFile.close();
	
	return importedRelation;
}


int main(){

	Relation importedTable = readFromFile("test.db");
	Relation table("foo");
	Relation table2("bar");
	Relation crossTable("cross");
	Relation unionTable("union");
	Relation diffTable("diff");
	
	dataType charType(false, 20);
	dataType intType(true);
	
	table.addAttribute("FOO", charType);
	table.addAttribute("REDDIT", charType);
	table.addAttribute("BAR", charType);
	
	table2.addAttribute("FOO", charType);
	table2.addAttribute("REDDIT", charType);
	table2.addAttribute("BAR", charType);
	
	vector<string> table1_input(3);
	table1_input[0] = "MINE";
	table1_input[1] = "SPLIN";
	table1_input[2] = "HALO";
	
	vector<string> table1_input2(3);
	table1_input2[0] = "DIABLO";
	table1_input2[1] = "SC2";
	table1_input2[2] = "HL1";

	vector<string> table2_input(3);
	table2_input[0] = "ZELDA";
	table2_input[1] = "PORTAL";
	table2_input[2] = "GHOST";
	
	Relation blah("hoo");
	blah.addAttribute("FOO", charType);
	blah.addAttribute("REDDIT", charType);
	blah.addAttribute("BAR", charType);
	
	/*
	blah.addTuple( table.constructTupleFromIndex(0) );
	vector<string> kop = table.constructTupleFromIndex(0);
	cout << ">>>>>>>>>>>>><<<<<<<<<<<<<\n";
	for(int i = 0; i < kop.size(); i++) {
		cout << kop[i] << '\t';
	}
	cout << ">>>>>>>>>>>>><<<<<<<<<<<<<\n";	
	wait(); */
	
	table.addTuple(table1_input);
	table.addTuple(table1_input2);
	
	table2.addTuple(table1_input);
	table2.addTuple(table2_input);
	
	crossTable.crossProduct(table, importedTable);
	unionTable.tableUnion(table, table2);
	diffTable.tableUnion(table, table2);
	
	
	cout << "Table:\n";
	table.print();
	cout << "----------------------------------------------\n";

	cout << "Table2:\n";
	table2.print();
	cout << "----------------------------------------------\n";

	
	cout << "Imported Table:\n";
	importedTable.print();
	cout << "----------------------------------------------\n";
	
	cout << "Cross Product of Table and Imported Table:\n";
	crossTable.print();
	cout << "----------------------------------------------\n";
	
	//wait();

	//writeToFile<Relation>(crossTable);
	
	cout << "o4ifjal;sefjaw;efljas\n";
	cout << crossTable.stringify() << '\n';
	cout << "o4ifjal;sefjaw;efljas\n";
	
	table.deleteTuple(1);
	cout << "Table after deleting index 1 (2nd row)\n";
	table.print();
	cout << "----------------------------------------------\n";
	
	cout << "Table and Table2 have same attributes?\n";
	if(unionTable.matchingAttributes(table, table2)) {
		cout << "True!\n";
	} else {
		cout << "False!\n";
	}
	cout << "----------------------------------------------\n";	
	
	cout << "Table + Table2\n";
	unionTable.print();
	cout << "----------------------------------------------\n";	
	
	//wait();

	return 0;
}




map<string,Relation*> relsInMem;	//need to release memory on exit

bool freeMemory(){
	cout<<"Freeing Memory:\n";
	cout<<"--Relations:\n";
	for( map<string,Relation*>::iterator relIt= relsInMem.begin(); relIt != relsInMem.end(); ++relIt){
		cout<<(*relIt).first<<" @ "<<relIt->second<<endl;
		delete relIt->second;
	}
	return true;
}

//CLOSE relation-name; //Writes Existing  Table to DB
bool closeRelation(string relationName){
    if(relsInMem.count(relationName)==0){
        //relation does not exist in memory
        return false;
    }
	//TODO: ELSE IF relationName.db does not exist, break? only pre existing tables can be called from CLOSE
	else{
		writeToFile<Relation>((*relsInMem[relationName]));
		delete relsInMem[relationName];
		relsInMem.erase(relationName);
		return true;
	}
	return false;
}

//WRITE relation-name; //Writes NEW Table to DB
bool writeRelation(string relationName){
	if(relsInMem.count(relationName)==0){
        //relation does not exist in memory
        return false;
    }
	//TODO: ELSE IF relationName.db DOES exist, break? only NEW tables can be called from WRITE?
	else{
		writeToFile<Relation>((*relsInMem[relationName]));
		delete relsInMem[relationName];
		relsInMem.erase(relationName);
		return true;
	}
	return false;
}

bool openRelation(string relationName){
	if(relsInMem.count(relationName)!=0){
		//relation already exists in memory!
		return false;
	}
	//TODO: ELSE IF relationName.db does NOT exist, break (return false)
	else{
		Relation* readRel = readFromFilePtr(relationName+".db");
		relsInMem.insert( pair<string,Relation*>(relationName,readRel) );
		return true;
	}
	return false;
}


bool ExecuteCommand(string Command){
	//Create Parser Instance with Debug=0; (no output, silent)
	Parser parserInst(0); //This should only be instanciated/constructed once, but this will work for now..
	int fails = parserInst.ParseProgramBlock(Command);
	if(fails!=0){
		cout<<"Input is not syntactically correct, returning\n";
		return false;
	}
	bool ret=false;
	
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
				alI+=2;
				int len = stringToInt(toks[alI]);
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
		
		ret = true;
		return ret;
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
		cout<<"tuple("<<vals.size()<<"):"<<vals[0]<<":"<<vals[1]<<":"<<vals[2]<<endl;
		relsInMem[relName]->addTuple(vals);
		ret=true;
		return ret;
	}else if(toks[tI]=="SHOW"){
	    string relName=toks[tI+1];
	    relsInMem[relName]->print();
	    ret=true;
	    return ret;
	}else if(toks[tI]=="WRITE"){
	    string relName=toks[tI+1];
	    bool suc = writeRelation(relName);
	    return suc;
	}else if(toks[tI]=="OPEN"){
		string relName = toks[tI+1];
		bool suc = openRelation(relName);
		return suc;
	}else if(toks[tI]=="EXIT"){
		bool suc = freeMemory();
		exit(1);
		return suc;
	}
	

	
	
	return false;
}


/*
int main(){
	

	bool res = ExecuteCommand("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
	res = ExecuteCommand("INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);");
	res = ExecuteCommand("INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);");
    res = ExecuteCommand("INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);");
    res = ExecuteCommand("INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);");
    res = ExecuteCommand("INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);");
    res = ExecuteCommand("SHOW animals;");
    res = ExecuteCommand("WRITE animals;");
	res = ExecuteCommand("OPEN animals;");
	//res = ExecuteCommand("EXIT;");	
	
	
	
	cout << "Press ENTER to continue";
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	

	return 0;
}*/
