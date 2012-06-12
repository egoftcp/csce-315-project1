/********************************************
 * Laramie Goode, Chris Voss, Curtis Franks	*
 * CSCE-315-Project_1						*
 * Database DBMS (WIP)						*
 ********************************************/

#include "stdlib.h" 
#include <string>
#include <map>
#include <vector>
#include <iostream>//|
#include <fstream>//|
#include <sstream>
#include "ParserEngine.h"
#include "DataType.h"
#include "Attribute.h"
#include "Relation.h"
#include "DBEngine.h"
//TODO: Determine if we need all headers


using namespace std;

class DBMS{
//A database management system (DBMS) is a software package with computer programs that control the creation, maintenance, and use of a database.
//Most database management systems include their own application programming interface (API) that allows the user 
//to interact with their underlying engine without going through the user interface of the DBMS.
//http://en.wikipedia.org/wiki/Database_management_system

public:	
	map<string,Relation*> relsInMem;
	ParserEngine* Parser;
	
	string DBPath;
	
	DBMS(bool CmdPrmptMode=true, int DebugMode=1, string DBPath="./"){
		debug = DebugMode;
		consoleMode = CmdPrmptMode;
		engine = new DBEngine(DBPath, &relsInMem);
		Parser = new ParserEngine(engine, &relsInMem, DebugMode);
		if(consoleMode){
			startConsole();
		}
	}
	
	//TODO: FOR dbengine testing. remove later
	Relation readFromFile(string input) { //TODO: Not needed, can remove 

		ifstream inputFile;
		inputFile.open(input.c_str());
		
		Relation r("NULL");
		if(!inputFile.good()){
			return r;
		}
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
	
	void Execute(string line){
		//check to see if line is syntatically correct
		//ParseEngine/doer
		//?return meaningful result?
		//--all commands will either succeded or fail.
		//--all queries will result in a new relation created in memory.
		//--only SHOW will have "output" (print relation to screen"
		
		int valid = Parser->Validate(line);
		if(valid==0){errOut("Invalid Query or Command Syntax |**| "+line); return;}
		else if(valid==1){
			if(!(Parser->ExecuteCommand(line))){ errOut("Unexpected error Executing Command: "+line);}
		}else if(valid==2){
			Relation* newRel = Parser->ExecuteQuery(line);
			//TODO: look here \/
			//if newRel == 0, errOut
			//if (relsInMem.count(newRel->getName())==1){not a new rel, already in mem. handle differntly or updatre relsInMem? errOut if addr is not same?}

			
			//NOTE: breaks if returned relation does not have a name
			string newRelName = newRel->getName();
			relsInMem[newRel->getName()]=newRel;
		}
	}

	/*
	bool WriteRelation(string relationName){//Write NEW Relation (view) to File (File cannot exist?), Then free(delete) from memory
		if(relsInMem->count(relationName)==0){
			//relation does not exist in memory
			errOut("Relation '" + relationName + "' not found in memory. Doing Nothing.");
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
	bool CloseRelation(string relationName){//(Over)Write Relation to File, Then free(delete) from memory
		 if(relsInMem.count(relationName)==0){
			//relation does not exist in memory
			errOut("Relation '" + relationName + "' not found in memory. Doing Nothing.");
			return false;
		}
		//TODO: ELSE IF relationName.db does not exist, break? QUESTION: only pre existing tables can be called from CLOSE
		else{
			writeToFile<Relation>((*relsInMem[relationName]));
			delete relsInMem[relationName];
			relsInMem.erase(relationName);
			return true;
		}
		return false;
	}	
	bool OpenRelation(string relationName){
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
	*/

	~DBMS(){
	if(!freeMemory()){
		throw "Error freeing memory on DBEngine Destruction";
	}
}

private:
	//Data Members:
	DBEngine* engine; //IDEA: low priority, Could easily build in support for multiple Databases. i.e. map<name,DBEngine*> myDBs, managing paths for each one
	int debug; //0-silent mode (supress output)
	bool consoleMode; //if true, DBMS will take over (output to) command prompt and wait for input from stdin. Otherwise, it can be used as normal class

	//Methods:
	void startConsole(){
		cout<<"\n\n\n**************************************************************\n";
		cout<<"*****Welcome to the Relational Database Management System*****\n";
		cout<<"\n\n\n**************************************************************\n";
		cout<<"\nTry some commands...\n\n";
		
		string input;
		cout<<"dbms::";
		getline(cin,input);
		
		while(input!="leave"){
			Execute(input);
			cout<<"dbms::";
			getline(cin,input);
		} 
		
	}
	bool freeMemory(){
		if(debug>=3){cout<<"Freeing Memory:\n-Relations:\n";}
		for( map<string,Relation*>::iterator relIt= relsInMem.begin(); relIt != relsInMem.end(); ++relIt){
			if(debug>=3){cout<<"--"<<(*relIt).first<<" @ "<<relIt->second<<endl;}
			delete relIt->second;
		}
		delete engine;
		delete Parser;
		return true; // is there any way to tell if memory was freed or if failed?
	}
	void errOut(string error){
		if(debug>0){
			cerr<<"****| ERROR |**| "<<error<<" |****"<<endl;
		}
	}
};


