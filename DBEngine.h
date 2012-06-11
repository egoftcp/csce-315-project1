/********************************************
 * Laramie Goode, Chris Voss, Curtis Franks	*
 * CSCE-315-Project_1						*
 * Database Engine (WIP)					*
 ********************************************/

 
#ifndef DBENGINE_H
#define DBENGINE_H
 
#include "stdlib.h" 
#include <string>
#include <map>
#include <vector>
#include <iostream>//|
#include <fstream>//|
#include <sstream>
#include <cstring> //<-
//#include "Parser.h"//<-TODO:Remove
//#include "ParserEngine.h"
#include "DataType.h"
#include "Attribute.h" //
#include "Relation.h"
//TODO: Determine if we need all headers



using namespace std;

//Utilities: 
//TODO: move to another utilities file, class/namespace
void close() {
	exit(0);
}
void wait() {
	char a;
	cin >> a;
}
/*bool isNum(char input) { //redefined 
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
}*/
/*string intToString(int number) { //redefined
	stringstream ss;
	ss << number;
	return ss.str();
}
*/
int stringToInt(string str){
	int i;
	stringstream ss(str);
	ss >> i;
	return i;
}

class DBEngine{
//A database engine (or "storage engine") is the underlying software component 
//that a database management system (DBMS) uses to create, read, update and delete (CRUD) data from a database.
//http://en.wikipedia.org/wiki/Database_engine

public:
	string dbFilePath;
	
	DBEngine(){
		dbFilePath = "./";
		
	}
	
	DBEngine(string SavePath){
		if(!setPath(SavePath)){
			dbFilePath = "./";
		}
	}
	
	bool setPath(string savePath){
		//TODO: Verify path exists and (optional) that process has access to write to location. Return false if anything goes wrong.
		dbFilePath = savePath;
		return true;
	}
	
	
	//Create:
	template <class DB_type>
	void writeToFile(DB_type writeFrom) { 
	//TODO: *add more functionality/error checking
	//*need differentiation of write vs overwrite.
	//*needs error handling (return false if file not found (or if it is found, it depends on the case) ) See below.
	//QUESTION: will we be reading/writing Attributes aswell, or just Relations?
		string filename = writeFrom.getName();
		filename = filename + ".db";
		
		ofstream outputFile;
		outputFile.open(filename.c_str());
		outputFile << writeFrom.stringify();
		outputFile.close();
		
	}
	bool UpdateRelation(Relation* rel){ //aka OverWriteExistingRelation()
		//If file ' dbFilePath+"//"+rel->getName()+".db" ' does not exist, return false
		//else, overwrite file. (delete existing file, write rel to file (with same name) )
	}
	bool WriteNewRelation(Relation* newRel){
		//check to see if file exists
		//---if so, return false
		//---else, write relation to file, then return true.
	}	
	bool RelationFileExists(string relName){
		//returns true if file @ dbPath+"//"+relName+".db"  exists
		//otherwise returns false
	}
		
	//Read:
	Relation readFromFile(string input) { //TODO: Not needed, can remove 

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
		//TODO: if inputFile did not open, return 0!
		
		
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

	//Update:
	//Probably will be moved to ParserEngine
	//Update attributes to values for each tuple index provided
	bool Update(string relationName, vector< pair<string,string> > AttributeNameNewValueList, vector<int> indices){
		//-read relation file to memory
		//--for each int i in indices{
		//----for each pair<string,string> attrPair in AttributeNameNewValueList){
		//------relsInMem[relationName].getAttribute[attrPait.first].cells[i] = attrPair.second;
		//----}
		//--}
		//-Overwrite relation to file
		//-relase memory

	}

	//Delete:
	bool Delete(string relationName, vector<int> indices){
		//-read relation file to memory
		//-delete tuple at each indice provided
		//-save(overwrite) relation file
		//-release relation from memory
	}
	
};


/*Old Mains
int main1(){

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
	
	//wait();

	//importedTable.print();

	//writeToFile<Relation>(table);
	
	table.deleteAttribute("REDDIT");
	
	table.print();

	wait();

	return 0;
}

int main2(){
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
}



//Commands (persistent results):
//CREATE - write new relation to file (
//INSERT - write tuples to relation file
//OPEN - load relation from file 
//SHOW -  ? print relation to stdout?
//WRITE - add a new relation to a file ???? writes a view to file?
//CLOSE - save (to file) changes to a relation 
//EXIT - exit from dml interpreter 

*/



#endif



