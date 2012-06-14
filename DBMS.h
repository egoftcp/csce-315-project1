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
#include "Helpers.h"
#include <fstream>//|
#include <sstream>
#include <queue>
//#include "ParserEngine.h"

#include "DataType.h"
#include "Attribute.h"
#include "Relation.h"
#include "CondConjCompOp.h"
#include<boost/tokenizer.hpp>
//#include "DBEngine.h"
//TODO: Determine if we need all headers


using namespace std;

class DBMS;
class DBEngine;
class ParserEngine;

//Class Method forward declarations 
class DBMS{
//A database management system (DBMS) is a software package with computer programs that control the creation, maintenance, and use of a database.
//Most database management systems include their own application programming interface (API) that allows the user 
//to interact with their underlying engine without going through the user interface of the DBMS.
//http://en.wikipedia.org/wiki/Database_management_system
public:
	map<string,Relation*> relsInMem;
	vector<Relation*> scratchRels;
	ParserEngine* Parser;
	DBEngine* dbEngine; //IDEA: low priority, Could easily build in support for multiple Databases. i.e. map<name,DBEngine*> myDBs, managing paths for each one
	string DBPath;
	DBMS(bool CmdPrmptMode, int DebugMode, string DBPath);
	Relation readFromFile(string input);
	void Execute(string line);
	int ExecuteTxtFile(string fileName);
	~DBMS();
	
private:
	int debug;
	bool consoleMode;
	bool freeMemory();
	void startConsole();
	void errOut(string error);
};

class DBEngine{
public:
	string dbFilePath;
	//map<string, Relation*>* relsInMemP;
	DBMS* ownerDBMS;
	
	DBEngine();
	DBEngine(string SavePath, DBMS* OwnerDBMS );
	bool setPath(string savePath);
	template <class DB_type>
	void writeToFile(DB_type writeFrom);
	void writeToFile(string relationName);
	bool UpdateRelation(Relation* rel); //aka OverWriteExistingRelation()
	bool WriteNewRelation(Relation* newRel);
	bool RelationFileExists(string relName);
	bool Delete(string relationName, vector<int> indices);
	bool Update(string relationName, vector< pair<string,string> > AttributeNameNewValueList, vector<int> indices);
	Relation* readFromFilePtr(string input);
	bool OpenRelation(string relationName);
	Relation readFromFile(string input);
};

class ParserEngine{
public:
	bool allowNonCaps;
	int debug;
	DBMS* ownerDBMS;
	vector<string> sToks;
	int sI;
	int level;
	ParserEngine(DBMS* OwnerDBMS, int Debug);
	ParserEngine(DBMS* OwnerDBMS, int Debug, bool AllowNonCapitalCMDs);
	void resetParserVals();
	void printSTok();
	int Validate(const string& line);
	Relation* ExecuteQuery(const string& Query);
	bool ExecuteCommand(const string& Command);
	int ParseProgramBlock(string Program);
	bool ParseSingleLine(string line);
	bool ParseTokens();
	
private:
	Relation* doProduct();
	string getRelationName(int* relS);
	Relation* doUpdate(int* upStart);
	string getLiteral(int* litS);
	string getAttributeName(int* attS);
	Conjunction getConjunction(int* conJ);
	Comparison getComparison(int* comP);
	Operation getOp(int* opI);
	Operand getOperand(int* opandI);
	Condition getCondition(int* conS);
	Relation* doSelect(int* selStart);
	Relation* doExpr(int* qStart);
	bool isProjection1(int pS);
	Relation* doProjection(int* pS);
	Relation* doAtomicExpr(int* aeStart);
	Relation* doRename(int* qStart);
	vector<string> getAttributeList(int* attrListS);
	vector<string> dbTokens(string commandLine);
	//Syntatic Grammar Functions:
	bool isAtomicExpr();
	bool isQuery();
	bool isSelection();
	bool isRenaming();
	bool isUnion();
	bool isProduct();
	bool isDifference();
	bool isExpr();
	bool isRelationName();
	bool isIdentifier();
	bool isAttributeList();
	bool isAttributeName();
	bool isType();
	bool isInteger();
	bool isLiteral();
	bool isTypedAttributeList();
	bool isCondition();
	bool isConjunction();
	bool isComparison();
	bool isOp();
	bool isOperand();
	bool isFCommand();
	bool isCommand();
	bool isOpen();
	bool isClose();
	bool isWrite();
	bool isExit();
	bool isShow();
	bool isCreate();
	bool isUpdate();
	bool isInsert();
	bool isDelete();
	bool isProjection();
	//Debug Functions:
	void errOut(string s);
	void enter(string name);
	void leave(string name);
	void spaces(int local_level);
};


DBMS::DBMS(bool CmdPrmptMode=true, int DebugMode=1, string DBPath="./"){
	debug = DebugMode;
	consoleMode = CmdPrmptMode;
	dbEngine = new DBEngine(DBPath, this);
	Parser = new ParserEngine(this, DebugMode);
	if(consoleMode){
		startConsole();
	}
}
DBMS::~DBMS(){
	if(!freeMemory()){
		throw "Error freeing memory on DBEngine Destruction";
	}
}
Relation DBMS::readFromFile(string input) { //TODO: Not needed, can remove 
		//TODO: FOR dbengine testing. remove later
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
void DBMS::Execute(string line){
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
bool DBMS::freeMemory(){
	if(debug>=3){cout<<"Freeing Memory:\n-Relations:\n";}
	for( map<string,Relation*>::iterator relIt= relsInMem.begin(); relIt != relsInMem.end(); ++relIt){
		if(debug>=3){cout<<"--"<<(*relIt).first<<" @ "<<relIt->second<<endl;}
		delete relIt->second;
	}
	for( int i=0; i<scratchRels.size(); i++){
		delete scratchRels[i];
	}
	delete dbEngine;
	delete Parser;
	return true; // is there any way to tell if memory was freed or if failed?
}	
void DBMS::startConsole(){
	cout<<"\n\n\n**************************************************************\n";
	cout<<"*****Welcome to the Relational Database Management System*****\n";
	cout<<"**************************************************************\n";
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
void DBMS::errOut(string error){
	if(debug>0){
		cerr<<"****| ERROR |**| "<<error<<" |****"<<endl;
	}
}
int DBMS::ExecuteTxtFile(string fileName){
	int failCount=0;
	ifstream inFile( fileName.c_str() );
	if(!inFile){
		return -1;
	}
	while(inFile.good() ){ 
		string line;
		//get next line and print, skip if blank line
		getline(inFile, line);
		if(line=="" || line=="\r\n" || line=="\n"){continue;} //Skip blank Lines
		
		int valid = Parser->Validate(line);
		cout<<"********\n"<<line<<"\nvalid:"<<valid<<endl;
		if(valid == 0){
			failCount++;
		}else if(valid==1){
			if(!(Parser->ExecuteCommand(line))){ 
				errOut("Unexpected error Executing Command: "+line);
			}
		}else if(valid==2){
			Relation* newRel = Parser->ExecuteQuery(line);
			//TODO: look here \/
			//if newRel == 0, errOut
			//if (relsInMem.count(newRel->getName())==1){not a new rel, already in mem. handle differntly or updatre relsInMem? errOut if addr is not same?}

			
			//NOTE: breaks if returned relation does not have a name
			string newRelName = newRel->getName();
			relsInMem[newRel->getName()]=newRel;
		}else{
			throw "UNKNOWN EXCEPTION source code: 1233";
		}
	}
	return failCount;
}


	

DBEngine::DBEngine(){
	dbFilePath = "./";
	
}
DBEngine::DBEngine(string SavePath, DBMS* OwnerDBMS ){
	if(!setPath(SavePath)){
		dbFilePath = "./";
	}
	ownerDBMS = OwnerDBMS;
}
bool DBEngine::setPath(string savePath){
	//TODO: Verify path exists and (optional) that process has access to write to location. Return false if anything goes wrong.
	dbFilePath = savePath;
	return true;
}
template <class DB_type>
void DBEngine::writeToFile(DB_type writeFrom) { 
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
void DBEngine::writeToFile(string relationName) { 
//TODO: *add more functionality/error checking
//*need differentiation of write vs overwrite.
//*needs error handling (return false if file not found (or if it is found, it depends on the case) ) See below.
//QUESTION: will we be reading/writing Attributes aswell, or just Relations?
	string filename = relationName + ".db";
	
	ofstream outputFile;
	outputFile.open(filename.c_str());
	outputFile << ownerDBMS->relsInMem[relationName]->stringify();
	outputFile.close();
	
}
bool DBEngine::UpdateRelation(Relation* rel){ //aka OverWriteExistingRelation()
	//If file ' dbFilePath+"//"+rel->getName()+".db" ' does not exist, return false
	//else, overwrite file. (delete existing file, write rel to file (with same name) )
	return false;
}
bool DBEngine::WriteNewRelation(Relation* newRel){
	//check to see if file exists
	//---if so, return false
	//---else, write relation to file, then return true.
	return false;

}	
bool DBEngine::RelationFileExists(string relName){
	//returns true if file @ dbPath+"//"+relName+".db"  exists
	//otherwise returns false
	return false;

}
Relation DBEngine::readFromFile(string input) { //TODO: Not needed, can remove 

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
bool DBEngine::OpenRelation(string relationName){
	if(ownerDBMS->relsInMem.count(relationName)!=0){
		//relation already exists in memory!
		cerr<<"<><><>"<<"Relation already exists in memory\n";
		return false;
	}
	//TODO: ELSE IF relationName.db does NOT exist, break (return false)
	else{
		Relation* readRel = readFromFilePtr(relationName+".db");
		ownerDBMS->relsInMem.insert( pair<string,Relation*>(relationName,readRel) );
		return true;
	}
	return false;
}
Relation* DBEngine::readFromFilePtr(string input) {
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
bool DBEngine::Update(string relationName, vector< pair<string,string> > AttributeNameNewValueList, vector<int> indices){
	
/*		ifstream inputFile;
		inputFile.open(relationName.c_str());
		
		
		string name = relationName.substr(0, input.size()-3);
		
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
		
		return importedRelation;*/

	//-read relation file to memory
	//--for each int i in indices{
	//----for each pair<string,string> attrPair in AttributeNameNewValueList){
	//------relsInMem[relationName].getAttribute[attrPait.first].cells[i] = attrPair.second;
	//----}
	//--}
	//-Overwrite relation to file
	//-relase memory
	return false;

	}
bool DBEngine::Delete(string relationName, vector<int> indices){
	//-read relation file to memory
	//-delete tuple at each indice provided
	//-save(overwrite) relation file
	//-release relation from memory
	return false;

}


ParserEngine::ParserEngine(DBMS* OwnerDBMS, int Debug=1):debug(Debug){
	allowNonCaps = true;
	ownerDBMS = OwnerDBMS;
	//relsInMemP=RelsInMemP;
	//engineP = EngineP;
	resetParserVals();
}
ParserEngine::ParserEngine(DBMS* OwnerDBMS, int Debug=1, bool AllowNonCapitalCMDs=false):debug(Debug), allowNonCaps(AllowNonCapitalCMDs){
	ownerDBMS = OwnerDBMS;
	//relsInMemP=RelsInMemP;
	//engineP = EngineP;
	resetParserVals();
}
void ParserEngine::resetParserVals(){
	sToks.clear();
	sI=0;
	level=0;
}
void ParserEngine::printSTok(){
		//cout<<"*******Scanner Tokens:\n";
		for(vector<string>::iterator it=sToks.begin(); it!=sToks.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
int ParserEngine::Validate(const string& line){
	resetParserVals();
	sToks= dbTokens(line);
	
	if(sToks.back() != ";"){
		return 0;
	}
	
	if(isCommand()){
			return 1; //1 represents a valid command
	}else{
		resetParserVals();
		sToks= dbTokens(line);
		cout<<"stoks.size()"<<sToks.size()<<endl;
		if(isQuery()){
			return 2; //2 represents a valid query
		}else{
			return 0; //Failed Syntatic Check
		}
	}
}
Relation* ParserEngine::ExecuteQuery(const string& Query){
	enter("EXECUTEQUERY");
	resetParserVals();
	sToks = dbTokens(Query);
	
	int queryS=0;
	string relName = sToks[queryS];
	queryS+=2;
	Relation* queryRel = doExpr(&queryS);
	
	queryRel->name=relName;
	
	ownerDBMS->relsInMem[relName] = queryRel;
	leave("EXECUTEQUERY");
	//TODO: MOVE IN IMPLEMENTATION
	return queryRel;
}
bool ParserEngine::ExecuteCommand(const string& Command){ //ASSUMES VALID INPUT
	bool ret=false;
	int tI=0;
	int* cmdI = &tI;
	resetParserVals();
	sToks = dbTokens(Command);
	if(sToks[tI] == "CREATE"){
		string relName = sToks[2];
		queue<string> attrNames;
		queue<int> attrTypes;
		//typed-attribute-list will always start at index=4 (but open paren @ 3) and end when a close-paren follows a data type (instead of a comma)
		int alI=3; //attribute-list-Index (alI)
		do{
			alI++;
			attrNames.push(sToks[alI]);
			alI++;
			string typeName = sToks[alI];
			if(typeName=="VARCHAR"){
				alI+=2;
				int len = Helpers::stringToInt(sToks[alI]);
				attrTypes.push(len);
				alI+=2;			
			}else if(typeName=="INTEGER"){
				attrTypes.push(0);
				alI++;
			}else{
				cerr<<"Something terrible happened in ExecuteCommand-Create-TypedAttributeList\n";
			}
		}while(sToks[alI]==",");
		alI+=3; //move index to open-paren of 'primary key' attribute-list
		queue<string> pkNames;
		do{
			alI++;
			pkNames.push(sToks[alI]);
			alI++;
		}while(sToks[alI]==",");
		Relation* newRel = new Relation(relName);
		while(!attrNames.empty()){
			DataType dt((attrTypes.front()==0?true:false),attrTypes.front());
			newRel->addAttribute(attrNames.front(),dt);
			attrNames.pop();
			attrTypes.pop();
		}
		while(!pkNames.empty()){
			newRel->primaryKeys.push_back(pkNames.front());
			pkNames.pop();
		}
		ownerDBMS->relsInMem.insert( pair<string,Relation*>(relName,newRel) );
		ret = true;
		return ret;
	}
	else if(sToks[tI] == "INSERT"){
		string relName = sToks[2];
		vector<string> vals;
		int intInd=5;
		do{
			intInd++;
			if(sToks[intInd]=="\""){
				intInd++;
				vals.push_back(sToks[intInd]);
				intInd+=2;
			}else if(sToks[intInd]=="-"){
				intInd++;
				vals.push_back("-"+sToks[intInd]);
				intInd++;
			}else{
				vals.push_back(sToks[intInd]);
				intInd++;
			}
		}while(sToks[intInd]==",");
		cout<<"tuple("<<vals.size()<<"):"<<vals[0]<<":"<<vals[1]<<":"<<vals[2]<<endl;
		ownerDBMS->relsInMem[relName]->addTuple(vals);
		ret=true;
		return ret;
	}
	else if(sToks[tI]=="SHOW"){
	    string relName=sToks[tI+1];
	    ownerDBMS->relsInMem[relName]->print();
	    ret=true;
	    return ret;
	}
	else if(sToks[tI]=="WRITE"){
	    string relName=sToks[tI+1];
	    bool suc = true; // TODO: need new db writing methods to support this
		ownerDBMS->dbEngine->writeToFile(relName); //TODO: change this when DBEngine writing changes
	    return suc;
	}
	else if(sToks[tI]=="OPEN"){
		string relName = sToks[tI+1];
		bool suc = ownerDBMS->dbEngine->OpenRelation(relName);
		return suc;
	}
	else if(sToks[tI]=="EXIT"){
		//bool suc = freeMemory();
		//TODO: need to fix
		
		
		exit(1);
		return false;
	}
	else if(sToks[tI]=="CLOSE"){
		string relName = sToks[tI+1];
		bool suc = false; // TODO: need new db writing methods to support this
		ownerDBMS->dbEngine->writeToFile(relName); //TODO: change this when DBEngine writing changes
	    suc = (ownerDBMS->relsInMem.erase(relName)==1?true:false);
		return suc;
		//delete existing relName.db
		//write in-memory version of relName to relName.db
		//free memory of relsInMem[relName] 
		//remove relName from relsInMem   //int erasedCount = relsInMem.erase(relName); if(erasedCount!=1){errOut("Error removing relName from memory map.");}
	}
	else if(sToks[tI]=="DELETE"){
	}
//UPDATE customers SET firstName = "+firstName+" WHERE userId = "+idToUpdate+";
//UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";
//UPDATE customers SET phoneNumber = "+phoneNumber+" WHERE userId = "+idToUpdate+";
//UPDATE dvds SET dvdId = "+dvdId+" WHERE inventoryNumber = "+idToUpdate+";
//UPDATE dvds SET dvdTitle = "+dvdTitle+" WHERE inventoryNumber = "+idToUpdate+";
//UPDATE rentals SET checkInDate = \""+checkInDate+"\" WHERE dvdId = "+dvdId+";
	else if(sToks[tI]=="UPDATE")
	{
		int upI = (*cmdI);
		Relation* newRel = doUpdate(&upI);
		(*cmdI) = upI;
		return true;
		
/*		string relName = sToks[2],attribToChange = sToks[4],valToChangeTo,attribForFinding,valToFind; 
		vector<string> vals;
		int intInd=6,rowIndex,colIndex;
		if(sToks[intInd]=="\""){
			intInd++;
			valToChangeTo=sToks[intInd];
			intInd+=3;
		}else{
			valToChangeTo=sToks[intInd];
			intInd+=2;
		}
		attribForFinding=sToks[intInd];
		intInd+=2;
		if(sToks[intInd]=="\""){
			intInd++;
			valToFind=sToks[intInd];
		}else{
			valToFind=sToks[intInd];
			intInd+=2;
		}
	    cout<<"find "+valToFind+" in the "+attribForFinding+" column and update the "+attribToChange+" in that tuple";
		colIndex= (ownerDBMS->relsInMem[relName]->findAttribute(attribForFinding));
		colIndex= (ownerDBMS->relsInMem[relName]->
		return "true";*/
	}
}
int ParserEngine::ParseProgramBlock(string Program){//TODO: kill off
	int failCount=0;
	string Sub="";
	size_t sPos=0;
	size_t ePos = Program.find(';');
	if(ePos==string::npos) failCount++;
	while(ePos!=string::npos){
		ePos++;
		Sub = Program.substr(sPos,ePos-sPos);
		if(!ParseSingleLine(Sub)){
			failCount++;
		}
		sPos=ePos;		
		ePos = Program.find(';',int(sPos));
	}
	return failCount;
}
bool ParserEngine::ParseSingleLine(string line){//TODO: kill off
	resetParserVals();
	sToks=dbTokens(line);	
		if(debug==1){
			cout<<endl<<line<<endl;
		}else if(debug > 1){
			cout<<"\n\n***************Input Line***************\n***";
			cout<<line<<endl<<"***"<<endl;
			cout<<"***";
			printSTok();
			cout<<"****************************************\n";
		}
		bool passedParse = ParseTokens();
		//Print results
		if(debug>3){ cout<<"****************************************\n"; }
		if(debug>1){ cout<<"***              "<<(passedParse?"PASSED":"FAILED")<<"              ***\n****************************************\n"; }
		return passedParse;
}
bool ParserEngine::ParseTokens(){//TODO: kill off
	bool passedParse;
	if(isFCommand()){
		passedParse = isCommand();
	}else{
		passedParse = isQuery();
	}
	return passedParse;
}
vector<string> ParserEngine::dbTokens(string commandLine){ //Scanner-Tokenizer
//FUNCTION DECLARATIONS  
	string first;
	string temp="";			//the temp string is needed in order to store tokens produced by tokenizer when it may
							//be necessary to concatenate them with adjoining tokens to keep appropriate values within
							//the the command together.
	bool openSymbol=false,closeSymbol=false,openQuote=false;	//these boolean variable are utilized to keep track of symbols
																//that may have multiple parts and to ensure that text within 
																//quotations is held together as one token, regardless of 
																//punctuation or spaces.
	boost::char_separator<char> separator(" \n","\"()+<>=-;,!");	//the tokenizer function allows for the declaration of ignored and
																	//returned symbols with the ignored before the comma
	vector<string> tokens;	//a vector of type string to store the tokens so they may be returned to the calling program
	boost::tokenizer< boost::char_separator<char> > possibleTokens(commandLine, separator);	//the boost library supplies this function
	//END OF FUNCTION DECLARATIONS
   
	for( boost::tokenizer< boost::char_separator<char> >::iterator position=possibleTokens.begin();
		position!=possibleTokens.end();
		++position){
	   if(openQuote==true)							//With each pass through this for loop, the position is iterated
	   {											//If statements are used to check each token against possible 
			if(*position=="\"")						//conjunctive symbols such as <=, ==, >==, etc.
			{										//The first priority of the conditional checking is for an open quotation.
				tokens.push_back(temp);				//If the passed command has quotations around two otherwise separated words,
				tokens.push_back(*position);		//such as "two words", the openQuote boolean flag will stay true until the
				temp="";							//quote is finished and the strings within are concatenated into a token.
				openSymbol=false;
				closeSymbol=false;
				openQuote=false;
			}
			else
				if(temp=="")
					temp=*position;
				else
				{
					first=*position;
					if(!isalpha(first[0]))
						temp=temp+*position;		//if the current string is a symbol and still within the quotation then
					else							//no space will be added.
						temp=temp+" "+*position;	//the temp string is storing the concatenated strings within the quotes,
				}									//using a space between if both strings are text.
	   }
	   else if(openSymbol==true)					//There are four types of data that this chain handles: openSybols, 
	   {											//closeSymbols, quotations, and strings that would be data or commands.
			if(*position=="\"")						//When the openSymbol was previously set to true, the current position
			{										//is then checked for another openSymbol that may need to be joined with the
				tokens.push_back(temp);				//previous or if the current position requires that a new flag be set to true.
				tokens.push_back(*position);
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=true;						//In this case a quotation is found and determined to be an opening quote.
			}
			else if(*position=="<"||*position=="="||*position=="-")
			{
				openSymbol=true;					//In this case an adjoining openSymbol is found and concatenated to the previous.
				temp=temp+*position;				//This conditional check handles <=, ==, and <- symbols.
			}
			else
			{
				tokens.push_back(temp);
				tokens.push_back(*position);
				temp="";
				openSymbol=false;
				closeSymbol=false;					//when no symbols are found in this case, the previous open symbol is tokenized
			}										//and the current string is tokenized as well.
	   }
	   else if(closeSymbol==true)
	   {
		   if(*position=="\"")
			{
				tokens.push_back(*position);
				temp="";
				openSymbol=false;
				closeSymbol=false;		
				openQuote=true;						//When the prior string was a closeSymbol and a quotation is found it can be
			}										//assumed this is an open quotation.
		   else if(*position==">"||*position=="=")
			{
				closeSymbol=true;					//Here an adjoining closeSymbol is found and concatenated to the previous symbol.
				temp=temp+*position;				//This handles the >= symbol.
			}
		   else if(*position=="-")
			{
				closeSymbol=false;					//If the previous symbol was a closeSymbol then <- will be accounted for.
				openSymbol=true;
				tokens.push_back(temp);
				temp=*position;

			}
		   else
			{
				tokens.push_back(temp);
				tokens.push_back(*position);		//Lastely, when the previous string was a closeSymbol and the current string is not 
				closeSymbol=false;					//a symbol, the previous symbol will be tokenized and the current string will be tokenized.
				temp="";
			}
	   }
	   else
	   {
		   if(*position=="\"")
		   {
				tokens.push_back(*position);
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=true;						//If the previous string was not a symbol and there was no previous openQuote, this quote
		   }										//will be treated as an opening quote.
		   else if(*position=="<"||*position=="="||*position=="-"||*position=="!")		//As with the previous conditional checks, this check
			{																			//accounts for all possible openSymbols.
				openSymbol=true;
				temp=temp+*position;
			}
		   else if(*position==">")
			{
				closeSymbol=true;
				temp=*position;
			}
		   else
		   {
				closeSymbol=false;
				openSymbol=false;
				tokens.push_back(*position);		//All other strings are tokenized.
				temp="";
		   }
	   }
   }
   return tokens;			//A vector full of the tokens ready for translation by the database engine.
}
Relation* ParserEngine::doExpr(int* qStart){
/*bool isExp = isSelection();
		
	if(!isExp){
		isExp=isProjection();
	}
	if(!isExp){
		isExp=isRenaming();
	}
	if(!isExp){
		isExp=isUnion();
	}
	if(!isExp){
		sI=exprI;
		isExp=isDifference();
	}
	if(!isExp){
		sI=exprI;
		isExp=isProduct();
	}
	if(!isExp){
		sI=exprI;
		isExp=isAtomicExpr();
	}
	if(!isExp){
		sI=exprI;
	}*/
	


	enter("doExpr");
	int qS=(*qStart);
	
	Relation* expRel;
	
	cout<<"qS:"<<qS<<endl;
	if(sToks[qS] == "select"){
		expRel = doSelect(&qS);
	}
	else if(isProjection1(qS)){
		expRel = doProjection(&qS);
	
	}
	else if(sToks[qS] == "rename"){
		expRel = doRename(&qS);
	}

	(*qStart) = qS;
	leave("doExpr");
	return expRel;	
}
vector<string> ParserEngine::getAttributeList(int* attrListS){
	enter("getATTRLIST");
	vector<string> attrs;
	int alS= (*attrListS);
	
	cout<<"\n\n\n\n";
	printSTok();
	cout<<"alS="<<alS<<"\n\n\n";
	
	
	
	while(sToks[alS]!=")"){
		attrs.push_back(sToks[alS]);
		alS++;
		if(sToks[alS]==","){
			alS++;
		}
	}
	(*attrListS)=alS;
	
	leave("getATTRLIST");
	return attrs;

}



Condition ParserEngine::getCondition(int* conS){
//condition ::= conjunction { || conjunction }
	enter("doCondition");
	int cS = (*conS);
	Condition cond;
	Conjunction conj=getConjunction(&cS);
	cond.conjunctions.push_back(conj);
	while(sToks[cS]=="||"){
		cS++;
		conj = getConjunction(&cS);
		cond.conjunctions.push_back(conj);
	}
	(*conS) = cS;
	leave("doCondition");
	return cond;
}
Conjunction ParserEngine::getConjunction(int* conJ){
//conjunction ::= comparison { && comparison }
	enter("getConjunction");
	int cS = (*conJ);
	Conjunction conj;
	Comparison comp = getComparison(&cS);
	conj.comparisons.push_back(comp);
	while(sToks[cS]=="&&"){
		cS++;
		comp = getComparison(&cS);
		conj.comparisons.push_back(comp);
	}
	(*conJ) = cS;
	leave("getConjunction");
	return conj;
}
Comparison ParserEngine::getComparison(int* comP){
//comparison ::= operand op operand | ( condition )
	enter("getComparison");
	int cS = (*comP);
	Comparison comp;
	
	
	if(sToks[cS]=="("){
		cS++;
		comp.isCondition=true;
		comp.cond=getCondition(&cS);
		cS++;
	}else{
		comp.isCondition=false;
		comp.operand1=getOperand(&cS);
		comp.op=getOp(&cS);
		comp.operand2=getOperand(&cS);
	}
	
	(*comP) = cS;
	leave("getComparison");
	return comp;
}
Operation ParserEngine::getOp(int* opI){
//enum opEnum {"=="=0, "!=", "<" , ">", "<=", ">="}
//enum Operation { Equality=0, NonEquality, LessThan, GreaterThan, LessThanEqual, GreaterThanEqual }; // ==, !=, <, >, <=, >=
	enter("getOp");
	int oI = (*opI);
	Operation oper;
	if(sToks[oI] == "=="){
		oper=Equality;
	}else if(sToks[oI] == "!="){
		oper=NonEquality;
	}else if(sToks[oI] == "<"){
		oper=LessThan;
	}else if(sToks[oI] == ">"){
		oper=GreaterThan;
	}else if(sToks[oI] == "<="){
		oper=LessThanEqual;
	}else if(sToks[oI] == ">="){
		oper=GreaterThanEqual;
	}
	oI++;
	(*opI) = oI;
	leave("getOp");
	return oper;
}
Operand ParserEngine::getOperand(int* opandI){
//operand ::= attribute-name | literal
	enter("getOperand");
	int opI = (*opandI);
	Operand opernd;
	
	string firstTok = sToks[opI];
	if(firstTok=="\"" || firstTok=="-" || isdigit(firstTok[0])){
		opernd.isAttribute = false;
		string lit = getLiteral(&opI);
		opernd.val=lit;
	}else{
		opernd.isAttribute = true;
		string aN = getAttributeName(&opI);
		opernd.val=aN;
	}
	(*opandI) = opI;
	leave("getOperand");
	return opernd;
}
string ParserEngine::getLiteral(int* litS){
	enter("getLiteral");
	int lS = (*litS);
	string litt="";
	if(sToks[lS]=="\""){
		lS++;
		while(sToks[lS] != "\""){
			litt+=sToks[lS];
			lS++;
		}
		lS++;
	}else if(sToks[lS]=="-"){
		litt+=sToks[lS];
		lS++;
		litt+=sToks[lS];
		lS++;
	}else{
		litt=sToks[lS];
		lS++;
	}
	(*litS) = lS;
	leave("getLiteral");
	return litt;
}
string ParserEngine::getAttributeName(int* attS){
	enter("getAttributeName");
	string nm=sToks[(*attS)];
	(*attS)++;
	leave("getAttributeName");
	return nm;
}
string ParserEngine::getRelationName(int* relS){
	enter("getRelationName");
	string rN=sToks[(*relS)];
	(*relS)++;
	leave("getRelationName");
	return rN;
}

Relation* ParserEngine::doUpdate(int* upStart){
	//UPDATE dots SET x1 = 0 WHERE x1 < 0;
	//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
	enter("doUpdate");
	int upI = (*upStart);
	upI++; //consume UPDATE token
	string relName = getRelationName(&upI);
	vector<string> attribNames;
	vector<string> lits;
	do{
		upI++; //consumer "SET" or "," token
		attribNames.push_back(getAttributeName(&upI));
		upI++; //consume "=" token
		lits.push_back(getLiteral(&upI));
	}while(sToks[upI]==",");
	upI++; //consume "WHERE" token
	Condition cond = getCondition(&upI);
	
	Relation* updateRel = ownerDBMS->relsInMem[relName];
	vector<int> updateTuples;
	int cellCnt = updateRel->columns[0].cells.size();
	for(int i=0; i<cellCnt; i++){
		if(cond.passes(updateRel,i)){
			updateTuples.push_back(i);
		}
	}

	for(vector<int>::iterator it = updateTuples.begin(); it!=updateTuples.end(); ++it){
		int tupleI = (*it);
		for(int at = 0; at<attribNames.size(); at++){
			cout<<"****"<<updateRel->findAttributeP(attribNames[at])->cells[tupleI]<<" : "<<lits[at]<<endl;
			updateRel->findAttributeP(attribNames[at])->cells[tupleI] = lits[at];
		}		
	}
	(*upStart)=upI;
	leave("doUpdate");
	return updateRel;
	
}
Relation* ParserEngine::doProduct(){
//product ::= atomic-expr * atomic-expr 
	/*enter("isProduct");
	bool isProd=false;
	if(isAtomicExpr()){
		if(sToks[sI]=="*"){
			sI++;
			if(isAtomicExpr()){
				isProd=true;
			}else{errOut("Expected <atomic-expr> to follow \"<atomic-expr> * \"");}
		}
	}		
	leave("isProduct");
	return isProd;*/
}


Relation* ParserEngine::doSelect(int* selStart){
	//high_hitters <- select (homeruns >= 40) baseball_players;
	//selection ::= select ( condition ) atomic-expr
	enter("doSelect");
	int ss = (*selStart);
	ss+=2;
	Condition cond = getCondition(&ss);
	ss++;
	Relation* frmRel = doAtomicExpr(&ss);
	Relation* newRel = new Relation("select");
	for(int i=0; i<frmRel->columns.size(); i++){
		newRel->addAttribute(frmRel->columns[i].name, frmRel->columns[i].type);
	}
		
	vector<int> passedTupInds();
	for(int i=0; i<frmRel->columns[0].cells.size(); i++){
			if(cond.passes(frmRel, i)){
				newRel->addTuple(frmRel->getTuple(i));
			}
	}
	
	(*selStart) = ss;
	ownerDBMS->scratchRels.push_back(newRel);
	
	
	leave("doSelect");
	return newRel;
	
	
	
}
Relation* ParserEngine::doAtomicExpr(int* aeStart){
	printSTok();
	cout<<"aeSTART+++++="<<(*aeStart)<<endl;
	enter("doAE");
	int aeS = (*aeStart);
	//TODO: IMPLEMENT REST!
	string relName=sToks[aeS];	
	leave("doAE");
	return ownerDBMS->relsInMem[relName];
	//if rel not in mem, open

}
Relation* ParserEngine::doProjection(int* qStart){

	int pS = (*qStart);
	pS+=2;
	vector<string> attrList= getAttributeList(&pS);
	
	pS++;
	
	Relation* fromRel = doAtomicExpr(&pS);
	
	Relation* newRel = new Relation("projectionRel");
	
	
	for(int i=0; i<attrList.size(); i++){
		string attrName = attrList[i];
		Attribute newAttr = fromRel->findAttribute(attrName);
		newRel->addAttribute(newAttr);
	}
	
	ownerDBMS->scratchRels.push_back(newRel);
	
	return newRel;
	
}
Relation* ParserEngine::doRename(int* qStart){
	int rS = (*qStart);
	rS+=2;
	vector<string> attrList= getAttributeList(&rS);
	rS++;
	Relation* fromRel = doAtomicExpr(&rS);
	
	Relation* newRel = new Relation("renamingRel");
	
	for(int i=0; i<attrList.size(); i++){
		string newAttrName = attrList[i];
		Attribute newAttr = fromRel->columns[i];
		newAttr.name=newAttrName;
		newRel->addAttribute(newAttr);
	}
	
	ownerDBMS->scratchRels.push_back(newRel);
	
	return newRel;
	
}
bool ParserEngine::isProjection1(int pS){
	return sToks[pS] == "project";
}
bool ParserEngine::isAtomicExpr(){
//atomic-expr ::= relation-name | ( expr )
	enter("isAtomicExpr");
	bool isAE=false;
	if(sToks[sI]=="("){
		//"atomic-expr ::= ( expr )" case
		sI++;
		if(isExpr()){
			if(sToks[sI]==")"){
				sI++;
				isAE=true;
			}else{errOut("Expected closing-paren for expression in atomic-expression");}
		}else{errOut("Expected expression to follow open-paren in atomic-expression");}
	}else if(isRelationName()){
		//"atomic-expr ::= relation-name" case
		isAE=true;
	}
	leave("isAtomicExpr");
	return isAE;
}
bool ParserEngine::isQuery(){
//query ::= relation-name <- expr ;
	enter("isQuery");
	bool isQ=false;
	if(isRelationName()){
		if(sToks[sI]=="<-"){
			sI++;
			if(isExpr()){
				isQ=true;
			}else{errOut("Expected <expr> after \"<relation-name> <-\" in Query");}
		}else{errOut("Expected \"<-\" after \"<relation-name>\" in Query");}
	}
	if( sI>=sToks.size() ){
		isQ=false;
	}else if(sToks[sI]!=";"){
		isQ=false;
	}
	leave("isQuery");
	return isQ;
}
bool ParserEngine::isSelection(){
//selection ::= select ( condition ) atomic-expr
	enter("isSelection");
	bool isSel=false;
	if(sToks[sI]=="select"){
		sI++;
		if(sToks[sI]=="("){
			sI++;
			if(isCondition()){
				if(sToks[sI]==")"){
					sI++;
					if(isAtomicExpr()){
						isSel=true;
					}else{errOut("Expected atomic-expression to follow \"select ( <condition> ) \"");}
				}else{errOut("Expected close-paren to follow \"select (<condition>\"");}
			}else{errOut("Expected <condition> to follow \"select (\"");}
		}else{errOut("Expected open-paren to follow \"select\"");}		
	}		
	leave("isSelection");
	return isSel;
}
bool ParserEngine::isProjection(){
// projection ::= project ( attribute-list ) atomic-expr
	enter("Projection");
	bool isProj=false;
	if(sToks[sI]=="project"){
		sI++;
		if(sToks[sI]=="("){
			sI++;
			if(isAttributeList()){
				if(sToks[sI]==")"){
					sI++;
					if(isAtomicExpr()){
						isProj=true;
					}else{errOut("Expected <atomic-expresion> to follow \"project ( <attribute-list> ) \"");}
				}else{errOut("Expected close-paren to follow \"project ( <attribute-list> \"");}
			}else{errOut("Expected <attribute-list> to follow \"project ( \"");}
		}else{errOut("Expected open-paren to follow \"project \"");}
	}
	leave("Projection");
	return isProj;
}
bool ParserEngine::isRenaming(){
// renaming ::= rename ( attribute-list ) atomic-expr
// rename_test <- rename (v_fname, v_lname, v_personality, v_bounty) enemies;
	enter("isRenaming");
	bool isRen=false;
	if(sToks[sI]=="rename"){
		sI++;
		if(sToks[sI]=="("){
			sI++;
			if(isAttributeList()){
				if(sToks[sI]==")"){
					sI++;
					if(isAtomicExpr()){
						isRen=true;
					}else{errOut("Expected <atomic-expresion> to follow \"rename ( <attribute-list> ) \"");}
				}else{errOut("Expected close-paren to follow \"rename ( <attribute-list> \"");}
			}else{errOut("Expected <attribute-list> to follow \"rename ( \"");}
		}else{errOut("Expected open-paren to follow \"rename \"");}
	}		
	leave("isRenaming");
	return isRen;
}
bool ParserEngine::isUnion(){
// union ::= atomic-expr + atomic-expr
	enter("isUnion");
	bool isUn=false;
	if(isAtomicExpr()){
		if(sToks[sI]=="+"){
			sI++;
			if(isAtomicExpr()){
				isUn=true;
			}else{errOut("Expected <atomic-expr> to follow \"<atomic-expr> + \"");}
		}
	}		
	leave("isUnion");
	return isUn;
}
bool ParserEngine::isProduct(){
//product ::= atomic-expr * atomic-expr 
	enter("isProduct");
	bool isProd=false;
	if(isAtomicExpr()){
		if(sToks[sI]=="*"){
			sI++;
			if(isAtomicExpr()){
				isProd=true;
			}else{errOut("Expected <atomic-expr> to follow \"<atomic-expr> * \"");}
		}
	}		
	leave("isProduct");
	return isProd;
}
bool ParserEngine::isDifference(){
// difference ::= atomic-expr - atomic-expr
	enter("isDifference");
	bool isDif=false;
	if(isAtomicExpr()){
		if(sToks[sI]=="-"){
			sI++;
			if(isAtomicExpr()){
				isDif=true;
			}else{errOut("Expected <atomic-expr> to follow \"<atomic-expr> - \"");}
		}
	}		
	leave("isDifference");
	return isDif;
}
bool ParserEngine::isExpr() {
//expr ::= atomic-expr | selection | projection | renaming | union | difference | product
	enter("isExpr");
	int exprI = sI;
	bool isExp = isSelection();
		
	if(!isExp){
		isExp=isProjection();
	}
	if(!isExp){
		isExp=isRenaming();
	}
	if(!isExp){
		isExp=isUnion();
	}
	if(!isExp){
		sI=exprI;
		isExp=isDifference();
	}
	if(!isExp){
		sI=exprI;
		isExp=isProduct();
	}
	if(!isExp){
		sI=exprI;
		isExp=isAtomicExpr();
	}
	if(!isExp){
		sI=exprI;
	}
	leave("isExpr");
	return isExp;
}
bool ParserEngine::isRelationName(){
//relation-name ::= identifier
	enter("isRelationName");
	bool isRel = isIdentifier();
	leave("isRelationName");
	return isRel;
}
bool ParserEngine::isIdentifier(){
//identifier ::= alpha { ( alpha | digit ) }
	bool isIdent=false;
	enter("isIdenfitier");
	string identif = sToks[sI];
	if(isalpha(identif[0]) || identif[0]=='_' ){
		isIdent=true;
		for(int i=1; i<identif.size(); i++){
			char c=identif[i];
			if( !(isalpha(c) || c=='_' || isdigit(c)) ){
				isIdent = false;
				break;
			}
		}
	}
	if(isIdent){
		sI++;
	}
	leave("isIdenfitier");
	return isIdent;
}
bool ParserEngine::isAttributeList(){
//attribute-list ::= attribute-name { , attribute-name } 
	enter("isAttributeList");
	bool isAL = false;
	if(isAttributeName()){
		isAL =true;
		int atNameSI = sI; //TODO: NOTE: this will be the first attribute name
		while(sToks[sI]==","){
			sI++;
			if(isAttributeName()){
				int atNamesSI = sI; //TODO: NOTE: these will be indexes to any following attribute names
			}else{isAL=false; errOut("Error within attribute-list, expected attribute name after comma");}
		}
	}else{errOut("Expected at least 1 attribute name in attribute-list");}
	
	leave("isAttributeList");
	return isAL;
}
bool ParserEngine::isAttributeName(){
//attribute-name ::= identifier
	enter("isAttributeName");
	bool isAttrib = false;
	isAttrib = isIdentifier();
	leave("isAttributeName");
	return isAttrib;
}
bool ParserEngine::isType(){
//type ::= VARCHAR ( integer ) | INTEGER
	enter("isType");
	bool isType = false;
	int tSi = sI;
	
	if(sToks[sI]=="INTEGER"){
		isType=true;
		sI++;
	}
	else if(sToks[sI]=="VARCHAR"){
		sI++;
		if(sToks[sI]=="("){
			sI++;
			if(isInteger()){
				int VarCountIndex=sI; //TODO: NOTE: this will be the index of the token representing the varchar count
				sI++;
				if(sToks[sI]==")"){
					sI++;
					isType=true;
				}else{errOut("Expected closing-paren following VARCHAR");}
			}else{errOut("Expected number following VARCHAR(");}
		}else{errOut("Expected open-paren after VARCHAR");}
	}
		
	if(!isType){
		sI = tSi;
	}
	leave("isType");
	return isType;
}
bool ParserEngine::isInteger(){
//integer ::= digit { digit }
	enter("isInteger");
	bool isInt=true;
	string intS = sToks[sI];
	for(int i=0; i<intS.size(); i++){
		if( !isdigit(intS[i]) ){
			isInt = false;
			break;
		}
	}
	leave("isInteger");
	return isInt;	
}
bool ParserEngine::isLiteral(){
	enter("isLiteral");
	int literalStartIndex = sI; 
	int literalEndIndex = sI;
	bool isLit=false;
	if(sToks[sI]=="\""){ //Quoted literal
		sI++; //consume open "
		literalStartIndex = sI;
		while(sToks[sI]!="\""){
			sI++; //consume literal bit
		}
		literalEndIndex = sI-1;
		sI++; // consume end "
		isLit=true;
	}else if(sToks[sI]=="-"){
		literalStartIndex = sI;
		sI++;
		literalEndIndex = sI;
		sI++;
		isLit=true;
	}else{ //Unquoted literal
		sI++; //consume unquoted literal 
		isLit=true;
	}
	leave("isLiteral");
	return isLit;
}
bool ParserEngine::isTypedAttributeList(){
//typed-attribute-list ::= attribute-name type { , attribute-name type }
	enter("isTypedAttributeList");
	int taSi = sI;
	bool isTA=false;
	if(isAttributeName()){
		if(isType()){
			isTA=true;
			while(sToks[sI]==","){
				sI++;
				if(isAttributeName()){
					if(isType()){
						;
					}else{isTA=false; errOut("Expected type after attribute name");}	
				}else{isTA=false; errOut("Expected typed-attribute-list");}
			}
		}else{errOut("Expected type after attribute name");}		
	}else{errOut("Expected typed-attribute-list");}
	
	if(!isTA){
		sI=taSi;
	}
	leave("isTypedAttributeList");
	return isTA;
}
bool ParserEngine::isCondition(){
//condition ::= conjunction { || conjunction }
	enter("isCondition");
	bool isCond = false;
	if(isConjunction()){
		isCond=true;
		while(sToks[sI]=="||"){
			sI++;
			if(isConjunction()){
				isCond = true;
			}else{isCond=false; errOut("Expected conjunction after \"||\"");}
		}
	}else{errOut("Expected at least 1 conjunction in condition");}
	leave("isCondition");
	return isCond;
}
bool ParserEngine::isConjunction(){
//conjunction ::= comparison { && comparison }
	enter("isConjunction");
	bool isConj = false;
	if(isComparison()){
		isConj=true;
		while(sToks[sI]=="&&"){
			sI++;
			if(isComparison()){
				isConj=true;
			}else{isConj=false; errOut("Expected comparison after \"&&\"");}
		}
	}else{errOut("Expected at least 1 comparison in conjunction");}
	leave("isConjunction");
	return isConj;
}
bool ParserEngine::isComparison(){
//comparison ::= operand op operand | ( condition )
	enter("isComparison");
	bool isComp = false;
	
	if(sToks[sI]=="("){
		sI++;
		if(isCondition()){
			if(sToks[sI]==")"){
				sI++;
				isComp=true;
			}else{errOut("Expected closing paren on condition within comparison");}
		}else{errOut("Expected condition after open-paren of comparison");}
	}else if(isOperand()){
		string operand1=sToks[sI-1];
		if(isOp()){
			string op=sToks[sI-1];
			if(isOperand()){
				string operand2 = sToks[sI-1];
				isComp=true;
			}
		}
	}
	leave("isComparison");
	return isComp;
}
bool ParserEngine::isOp(){
//enum opEnum {"=="=0, "!=", "<" , ">", "<=", ">="}
	enter("isOp");
	bool isop = true;
	if(sToks[sI] == "=="){
		
	}else if(sToks[sI] == "!="){
	
	}else if(sToks[sI] == "<"){
	
	}else if(sToks[sI] == ">"){
	
	}else if(sToks[sI] == "<="){
	
	}else if(sToks[sI] == ">="){
	
	}else{
		isop=false;
		//Not an 'op'
	}
	
	if(isop){
		sI++;
	}
	leave("isOp");
	return isop;
}
bool ParserEngine::isOperand(){
//operand ::= attribute-name | literal
	enter("isOpand");
	bool isOpand = false;
	if(isAttributeName()){
		isOpand=true;
	}else if(isLiteral()){
		isOpand=true;
	}
	leave("isOperand");
	return isOpand;
}
bool ParserEngine::isFCommand(){ 
//Determines if first token matches a Command
	string f = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	return ( (f=="OPEN") || (f=="CLOSE") || (f=="WRITE") || (f=="EXIT") || (f=="SHOW") || (f=="CREATE") || (f=="UPDATE") || (f=="INSERT") || (f=="DELETE") );
}
bool ParserEngine::isCommand(){
//command ::= ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
	enter("isCommand");
	bool isCmd = false;
	if(isFCommand()){
		if(isOpen() || isClose() || isWrite() || isExit() || isShow() || isCreate() || isUpdate() || isInsert() || isDelete()){
			if(sToks[sI]==";"){
				isCmd=true;
			}else{errOut("Expected ; after command!");}
		}
	}
	leave("isCommand");
	return isCmd;
}
bool ParserEngine::isOpen(){
//open-cmd ::== OPEN relation-name
	enter("isOpen");
	bool isOpn=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="OPEN"){
		sI++;
		if(isRelationName()){
			string relName=sToks[sI-1];
			isOpn=true;
		}else{ errOut("Expected 'relation-name' after \"OPEN\" command."); }
	}
	leave("isOpen");
	return isOpn;
}
bool ParserEngine::isClose(){
//close-cmd ::== CLOSE relation-name
	enter("isClose");
	bool isCls=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="CLOSE"){
		sI++;
		if(isRelationName()){
			string relName=sToks[sI-1];
				isCls=true;
				//TODO: DBENG: this is where we can call dbEng.CLOSE(relName);
		}else{ errOut("Expected 'relation-name' after \"CLOSE\" command."); }
	}
	leave("isClose");
	return isCls;
}
bool ParserEngine::isWrite(){
//write-cmd ::== WRITE relation-name
	enter("isWrite");
	bool isWrt=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);	
	if(sToks[sI]=="WRITE"){
		sI++;
		if(isRelationName()){
			string relName=sToks[sI-1];
				isWrt=true;
				//TODO: DBENG: this is where we can call dbEng.WRITE(relName);
		}else{ errOut("Expected 'relation-name' after \"WRITE\" command."); }
		leave("WRITE");
	}
	leave("isWrite");
	return isWrt;
}
bool ParserEngine::isExit(){
//exit-cmd ::== EXIT
	enter("isExit");
	bool isExt=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="EXIT"){
		sI++;
		isExt=true;
	}
	leave("isExit");
	return isExt;
}
bool ParserEngine::isShow(){
//show-cmd ::== SHOW atomic-expr
	enter("isShow");
	bool isShw=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="SHOW"){
		sI++;
		int atomicExprSI=sI;
		if(isAtomicExpr()){
			int atomicExprEI=sI-1;
				isShw=true;
				//TODO: DBENG: this is where we can call dbEng.atomicExp(atomicExpr);  sToks[cmdSi] sToks[sI-1]
		}else{ errOut("Expected 'atomic-expression' after \"SHOW\" command."); }
	}
	leave("isShow");
	return isShw;
}
bool ParserEngine::isCreate(){
//create-cmd ::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
	enter("isCreate");
	bool isCrt=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="CREATE"){
		sI++;
		sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
		if(sToks[sI] == "TABLE"){
			sI++;
			if(isRelationName()){
				string relName=sToks[sI-1];
				if(sToks[sI] == "(" ){
					sI++;
					int typedAttrLstSI=sI;
					if(isTypedAttributeList()){
						int typedAttrLstEI=sI-1;
						//vector<TypedAttribute> typedAttrs = TypedAttributeList();
						if(sToks[sI]==")"){
							sI++;
							string tempP = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //TODO: IDEA: should we combine 'primary' and 'key' as they should never be apart?
							if(tempP=="PRIMARY"){
								sI++;
								string tempK = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
								if(tempK=="KEY"){
									sI++;
									if(sToks[sI]=="("){
										sI++;
										if(isAttributeList()){
											if(sToks[sI]==")"){
												sI++;
												isCrt=true;
											}else{errOut(" Expected closing-paren after \"CREATE TABLE "+relName+" ( <typed-attribute-list> ) PRIMARY KEY (<attribute-list>\"");}							
										}else{ errOut(" Error in attribute list after \"CREATE TABLE "+relName+" ( <typed-attribute-list> ) PRIMARY KEY (\"");}		
									}else{ errOut(" Expected open-paren after \"CREATE TABLE "+relName+" ( <typed-attribute-list> ) PRIMARY KEY\"");}
								}else{errOut(" Expected \"KEY\" After \"CREATE TABLE "+relName+" ( <typed-attribute-list> ) PRIMARY \""); }
							}else{errOut(" Expected \"PRIMARY\" After \"CREATE TABLE "+relName+" ( <typed-attribute-list> )\""); }
						}else{errOut("After \"CREATE TABLE "+relName+" ( <typed-attribute-list> \" , Expected closing-paren."); }
					}else{errOut("After \"CREATE TABLE "+relName+"(\". Error in typed-attribute-list, or did not find typed-attribute-list"); }
				}else{errOut("After \"CREATE TABLE "+relName+"\", Expected open-paren then typed-attribute-list. Did not find open-paren");}
			}else{ errOut("Expected 'relation-name' after \"CREATE TABLE\" command."); }
		}else{errOut("Expected \"TABLE\" to follow \"CREATE\"");}
	}
	leave("isCreate");
	return isCrt;
}
bool ParserEngine::isUpdate(){
//UPDATE dots SET x1 = 0 WHERE x1 < 0;
//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
	enter("isUpdate");
	bool isUpd=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="UPDATE"){
		sI++;
		if(isRelationName()){
			string relName=sToks[sI-1];
			if(sToks[sI]=="SET"){
				sI++;
				//loop look here
				if(isAttributeName()){
					string attrName=sToks[sI-1];
					if(sToks[sI]== "="){
						sI++;
						if(isLiteral()){
							//TODO: FIX: some looping needed 
							while(sToks[sI]==","){ cout<<"\n\n\nERROR, NO SUPPORT FOR MULTIPLE ATTRIBUTE-NAME ASSIGNMENTS YET\n\n\n"; return false; sI++;}
							if(sToks[sI]=="WHERE"){
								sI++;
								if(isCondition()){
									isUpd=true;
								}else{errOut("error in condition");}
							}else{errOut("expected \"WHERE\"");}
						}else{errOut("Error in literal");}						
					}else{errOut("Expected \"=\" after \"UPDATE "+relName+" SET "+attrName+"\"");}
				}else{errOut("Expected <attribute-name> after \"UPDATE "+relName+" SET \"");}
			}else{errOut("Expected \"SET\" after \"UPDATE "+relName+"\"");}
		}else{errOut("Expected relation-name after UPDATE");}
	}
	leave("isUpdate");
	return isUpd;
}
bool ParserEngine::isInsert(){
// insert-cmd ::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) 
			//  | INSERT INTO relation-name VALUES FROM RELATION expr
	enter("isInsert");
	bool isIns=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="INSERT"){
		sI++;
		sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'INTO'
		if(sToks[sI]=="INTO"){
			sI++;
			if(isRelationName()){
				sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'VALUES'
				if(sToks[sI]=="VALUES"){
					sI++;
					sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'FROM'
					if(sToks[sI] =="FROM"){
						sI++;
						string temp= (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for !!possible!! 'RELATION' token
						if(temp=="RELATION"){
							//This is < VALUES FROM RELATION expr > case of 'INSERT'
							sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'RELATION' token
							sI++; //consume 'RELATION'
							if(isExpr()){
								isIns=true;
							}else{errOut("Expected expression to follow \"INSERT INTO relation-name VALUES FROM RELATION\"");}
						}else if(sToks[sI]=="("){
							//This is the < VALUES FROM (literal{,literal}) > case of 'INSERT'
							sI++;
							if(isLiteral()){
								while(sToks[sI]==","){
									sI++;
									if(isLiteral()){
										; //TODO: POSSIBILITY: can handle individuals literals here.
									}else{isIns=false; errOut("Expected Literal to follow ',' in \"INSERT INTO relation-name VALUES FROM ( literal { , literal } )\"");}
								}
							}
							if(sToks[sI]==")"){
									sI++;
									isIns=true;
							}else{errOut("Expected ')' to follow 'INSERT INTO relation-name VALUES FROM ( literal { , literal } '");}
						}else{errOut("Expected 'RELATION' or '( literal { , literal } )' after \"INSERT INTO <relation-name> VALUES FROM\"");}
					}else{errOut("Expected 'FROM' after \"INSERT INTO <relation-name> VALUES\"");}
				}else{errOut("Expected 'VALUES' after \"INSERT INTO <relation-name>\"");}
			}else{errOut("expected <relation-name> after 'INSERT INTO'");}
		}else{errOut("expected 'INTO' after 'INSERT'");}		
	}
	leave("isInsert");
	return isIns;	
}
bool ParserEngine::isDelete(){
//delete-cmd ::= DELETE FROM relation-name WHERE condition
	enter("isDelete");
	bool isDel=false;
	sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]);
	if(sToks[sI]=="DELETE"){
		sI++;
		sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'FROM'
		if(sToks[sI]=="FROM"){
			sI++;
			if(isRelationName()){
				sToks[sI] = (allowNonCaps?Helpers::retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'WHERE'
				if(sToks[sI]=="WHERE"){
					sI++;
					if(isCondition()){
						isDel=true;
					}else{errOut("Expected <condition> to follow \"DELETE FROM relation-name WHERE\"");}
				}else{errOut("Expected \"WHERE\" to follow \"DELETE FROM <relation-name>\"");	}
			}else{errOut("Expected <relation-name> to follow \"DELETE FROM\"");	}
		}else{errOut("Expected \"FROM\" to follow \"DELETE\"");}
	}
	leave("isDelete");
	return isDel;
}

//Debug Functions:
void ParserEngine::errOut(string s) {
	if(debug>2){
		cout<<"\n*** ERROR: "<<s<<endl;
	}	
}
void ParserEngine::enter(string name) {
	if(debug>3&& sI<sToks.size() ){
		spaces(level++);
		cout<<"+-"<<name<<": Enter, \t";
		cout<<"Tok == "<<sToks[sI]<<endl;
	}
}
void ParserEngine::leave(string name) {
	if(debug>3 && sI<sToks.size() ){
		spaces(--level);
		cout<<"+-"<<name<<": Leave, \t";
		cout<<"Tok == "<<sToks[sI]<<endl;
	}
}
void ParserEngine::spaces(int local_level) {
	if(debug>3){
		while (local_level-- > 0) {cout<<"| ";}
	}
}






