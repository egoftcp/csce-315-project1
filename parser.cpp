/* parser.cpp:
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include<boost/tokenizer.hpp>

using namespace std;


class DType{ //TODO: change to struct
public:
	bool isVARCHAR; //false means dType is INTEGER
	int charCnt; //meaningless if !isVARCHAR
};

class TypedAttribute{ //TODO: change to struct
public:
	string attrName;
	DType dType;
};

vector<string> dbTokens(string commandLine){
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

class Parser{
public:
	bool allowNonCaps;
	vector<string> sToks;
	int sI;
	//string sTok(){retrn sToks[sI];}
	

#pragma region MYREGION
	vector<string> sTokens;
	vector<string> pTokens;
	int sTokI;
	string sTok;
	int level;

	void addPTok(string pTok){
		pTokens.push_back(pTok);
		cout<<"**Parser Tokens: ";
		for(vector<string>::iterator it=pTokens.begin(); it!=pTokens.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
	
#pragma endregion

	void printPTok(){
		cout<<"**Parser Tokens: ";
		for(vector<string>::iterator it=pTokens.begin(); it!=pTokens.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
	
	void printSTok(){
		cout<<"**Scanner Tokens: ";
		for(vector<string>::iterator it=sToks.begin(); it!=sToks.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
	
	void getSTok(){
		sTokI++;
		sTok = sTokens[sTokI];
	}
	
	Parser(){
		level=0;
	}
	Parser(string fileName){
		level=0;
		allowNonCaps = true;
		ifstream inFile( fileName.c_str() );
		//Need to put in loop, splitting prog on '\n' or ';' , then handle each CorQ
		while(inFile.good() ){ //assuming infile will be newLine seperated
			
			//--
			sTokens.clear();
			pTokens.clear();
			sTokI=0;
			sTok="";
			//--
			sToks.clear();
			sI=0;
			
			
			level=0;
			string line;
			getline(inFile, line);	//function in/of <string> lib
			if(line==""){continue;} //Skip blank Lines
			cout<<"\n\n\n******************************\n**Handling Line: "<<line<<endl;
			
			/*Get Tokens
			sTokens = dbTokens(line);
			sTok= sTokens[0];
			*/
			sToks=dbTokens(line);
			
			
			
			//Print Tokens
			printSTok(); cout<<endl;
			
			//Parse
			bool passedParse = ParseTokens();
			
			cout<<"\n\n"<< (passedParse?"PASSED":"FAILED") << " on input line:\n"<<line<<endl;
			cout<<"**Done handling line\n****************************\n";
			cout << "Press ENTER to continue";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	bool ParseTokens(){
		bool passedParse;
		if(isFWordCommand(sToks[sI])){
			passedParse = isCommand();
		}else{
			passedParse = ParseQuery();
		}
		return passedParse;
	}

	bool isFWordCommand(string fWord){
		fWord = (allowNonCaps?retUpper(fWord):fWord);
		
		if(fWord=="OPEN"){
		
		}else if(fWord=="CLOSE"){
		
		}else if(fWord=="WRITE"){
		
		}else if(fWord=="EXIT"){
		
		}else if(fWord=="SHOW"){

		}else if(fWord=="CREATE"){

		}else if(fWord=="UPDATE"){
		
		}else if(fWord=="INSERT"){
		
		}else if(fWord=="DELETE" ){
		
		}else{
			return false;
		}
		return true;
	}

	//TODO: (re)Implement:
	bool isAtomicExpr(){
		int aeSi = sI;
		if(isRelationName() || isExpr()){
			return true;
		}
		else{
			sI=aeSi;
			return false;
		}
	}
	
	//expr ::= atomic-expr | selection | projection | renaming | union | difference | product
	bool isExpr() {
		return false;
		enter("Expression");
		bool isExpr = projection();
		if(!isExpr){
			isExpr=selection();
			if(!isExpr){
				isExpr=product();
				if(!isExpr){
					isExpr=renaming();
					if(!isExpr){
						isExpr=unionF();
						if(!isExpr){
							isExpr=difference();
							if(!isExpr){
								isExpr=atomicExpr();
							}
						}
					}
				}
			}
		}
		leave("Expression");
		return isExpr;
	}

	/*
	string AtomicExpr(){
		return "NULL";
	}
	vector<TypedAttribute> TypedAttributeList(){ //TODO: Question: perhaps take in a POINTER to a !COPY! of sTokI and manipulate/return it to represent end of TypedAttributeList?
		vector<TypedAttribute> attrList;
		
		return attrList;
	}*/
	
	//relation-name ::= identifier
	bool isRelationName(){
		enter("isRelationName");
		bool isRel = isIdentifier();
		leave("isRelationName");
		return isRel;
	}
	
	//identifier ::= alpha { ( alpha | digit ) }
	bool isIdentifier(){
		bool isIdentifier=false;
		enter("isIdenfitier");
		string identif = sToks[sI];
		if(isalpha(identif[0]) || identif[0]=='_' ){
			isIdentifier=true;
			for(int i=1; i<identif.size(); i++){
				char c=identif[i];
				if( !(isalpha(c) || c=='_' || isdigit(c)) ){
					isIdentifier = false;
					break;
				}
			}
		}
		leave("isIdenfitier");
		return isIdentifier;
	}
	
	//attribute-list ::= attribute-name { , attribute-name } 
	bool isAttributeList(){
		enter("isAttributeList");
		bool isAL = false;
		if(isAttributeName()){
			isAL =true;
			int atNameSI = sI; //TODO: NOTE: this will be the first attribute name
			sI++;
			while(sToks[sI]==","){
				sI++;
				if(isAttributeName()){
					int atNamesSI = sI; //TODO: NOTE: these will be indexes to any following attribute names
					sI++;
				}else{isAL=false; errOut("Error within attribute-list, expected attribute name after comma");}
			}
		}else{errOut("Expected at least 1 attribute name in attribute-list");}
		
		leave("isAttributeList");
		return isAL;
	}
	
	//attribute-name ::= identifier
	bool isAttributeName(){
		enter("isAttributeName");
		bool isAttrib = false;
		isAttrib = isIdentifier();
		leave("isAttributeName");
		return isAttrib;
	}
	
	//type ::= VARCHAR ( integer ) | INTEGER
	bool isType(){
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
	
	//integer ::= digit { digit }
	bool isInteger(){
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

	bool isLiteral(){//TODO: enhance, currently only supports single word literals with no quotes. i.e.  UPDATE dots SET x1 = 0 WHERE x1 < 0;  // 0 is literal
		enter("isLiteral");
		bool isLit=false;
		if(sToks[sI]=="\""){
			cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! quotations around literals needs to be implemented\n";
		}else{
			isLit=true;
		}
		leave("isLiteral");
		return isLit;
	}
	
	//typed-attribute-list ::= attribute-name type { , attribute-name type }
	bool isTypedAttributeList(){
		enter("isTypedAttributeList");
		int taSi = sI;
		bool isTA=false;
		//TODO: change to do-while
		if(isAttributeName()){
			sI++;
			if(isType()){
				//sI++;
				//cout<<"&&&&&&&&&&&&&&&: "<<sToks[sI]<<endl;
				isTA=true;
				while(sToks[sI]==","){
					sI++;
					if(isAttributeName()){
						sI++;
						if(isType()){
							//sI++;
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

	
	//condition ::= conjunction { || conjunction }
	bool isCondition(){
		enter("isCondition");
		bool isCond = false;
		if(isConjunction()){
			isCond=true;
			//sI++;
			while(sToks[sI]=="||"){
				sI++;
				if(isConjunction()){
					isCond = true;
					//sI++;
				}else{isCond=false; errOut("Expected conjunction after \"||\"");}
			}
		}else{errOut("Expected at least 1 conjunction in condition");}
		leave("isCondition");
		return isCond;
	}

	//conjunction ::= comparison { && comparison }
	bool isConjunction(){
		enter("isConjunction");
		bool isConj = false;
		if(isComparison()){
			isConj=true;
			//sI++;
			while(sToks[sI]=="&&"){
				sI++;
				if(isComparison()){
					isConj=true;
					//sI++;
				}else{isConj=false; errOut("Expected comparison after \"&&\"");}
			}
		}else{errOut("Expected at least 1 comparison in conjunction");}
		leave("isConjunction");
		return isConj;
	}

	//comparison ::= operand op operand | ( condition )
	bool isComparison(){
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
			string operand=sToks[sI];
			sI++;
			if(isOp()){
				string op=sToks[sI];
				cout<<"FOUND OP: "<<op<<endl;
				sI++;
				if(isOperand()){
					string operand2 = sToks[sI];
					sI++;
					isComp=true;
				}
			}
		}
		leave("isComparison");
		return isComp;
	}

	//enum opEnum {"=="=0, "!=", "<" , ">", "<=", ">="}
	bool isOp(){
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
		leave("isOp");
		return isop;
	}

	//operand ::= attribute-name | literal
	bool isOperand(){
		enter("isOpand");
		bool isOpand = false;
		if(isAttributeName()){
			//sI++;
			isOpand=true;
		}else if(isLiteral()){
			//sI++;
			isOpand=true;
		}
		leave("isOperand");
		return isOpand;
	}

	
	//TODO: test functionality
	string retUpper(string inStr){
		string upp = inStr;
		for(string::iterator it = upp.begin(); it!=upp.end(); ++it){
			*it = std::toupper((unsigned char)(*it));
		}
		return upp;
	}
	
	
// create-cmd ::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
// update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
// insert-cmd ::= INSERT INTO relation-name VALUES FROM ( literal { , literal } )
		   // | INSERT INTO relation-name VALUES FROM RELATION expr
// delete-cmd ::= DELETE FROM relation-name WHERE condition


	//command ::= ( open-cmd | close-cmd | write-cmd | exit-cmd | show-cmd | create-cmd | update-cmd | insert-cmd | delete-cmd ) ;
	bool isCommand(){
		bool isCmd=false;
		int cmdSi = sI;		
		string fWord = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
	
		// open-cmd ::== OPEN relation-name
		if(fWord=="OPEN"){
			enter("OPEN");
			sI++;
			if(isRelationName()){
				string relName=sToks[sI];
				sI++;
				if(sToks[sI]==";"){
					isCmd=true;
					cout<<"xxx Well-formed Command to 'OPEN' relation with name '"<<relName<<"'\n";
					//TODO: DBENG: this is where we can call dbEng.Open(relName);
				}else{ errOut("Expected semi-colon (';') at end of \"OPEN\" command."); }
			}else{ errOut("Expected 'relation-name' after \"OPEN\" command."); }
			leave("OPEN");
		}
		
		// close-cmd ::== CLOSE relation-name
		else if(fWord=="CLOSE"){
			enter("CLOSE");
			sI++;
			if(isRelationName()){
				string relName=sToks[sI];
				sI++;
				if(sToks[sI]==";"){
					isCmd=true;
					cout<<"xxx Well-formed Command to 'CLOSE' relation with name '"<<relName<<"'\n";
					//TODO: DBENG: this is where we can call dbEng.CLOSE(relName);
				}else{ errOut("Expected semi-colon (';') at end of \"CLOSE\" command."); }
			}else{ errOut("Expected 'relation-name' after \"CLOSE\" command."); }
			leave("CLOSE");
		}
		
		//write-cmd ::== WRITE relation-name
		else if(fWord=="WRITE"){
			enter("WRITE");
			sI++;
			if(isRelationName()){
				string relName=sToks[sI];
				sI++;
				if(sToks[sI]==";"){
					isCmd=true;
					cout<<"xxx Well-formed Command to 'WRITE' relation with name '"<<relName<<"'\n";
					//TODO: DBENG: this is where we can call dbEng.WRITE(relName);
				}else{ errOut("Expected semi-colon (';') at end of \"WRITE\" command."); }
			}else{ errOut("Expected 'relation-name' after \"WRITE\" command."); }
			leave("WRITE");
		}
		
		// exit-cmd ::== EXIT
		else if(fWord=="EXIT"){
			enter("EXIT");
			sI++;
			if(sToks[sI]==";"){
				isCmd=true;
				cout<<"xxx Well-formed Command to 'EXIT'\n";
				//TODO: DBENG: this is where we can call dbEng.EXIT();
			}else{ errOut("Expected semi-colon (';') at end of \"EXIT\" command."); }
			leave("EXIT");
		}

		// show-cmd ::== SHOW atomic-expr		
		else if(fWord=="SHOW"){ //TODO: Need to implement isExpr() from isAtomicExpr()
			enter("SHOW");
			sI++;
			if(isAtomicExpr()){
				sI++;
				if(sToks[sI]==";"){
					isCmd=true;
					cout<<"xxx Well-formed Command to 'SHOW' atomic-expression '\n"; //<<atomicExpr<<"'\n";
					//TODO: DBENG: this is where we can call dbEng.atomicExp(atomicExpr);  sToks[cmdSi] sToks[sI-1]
				}else{ errOut("Expected semi-colon (';') at end of \"SHOW\" command."); }
			}else{ errOut("Expected 'atomic-expression' after \"SHOW\" command."); }
			leave("SHOW");
		}
		
		// create-cmd ::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
		else if(fWord=="CREATE"){
			enter("CREATE");
			sI++;
			string sWord = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
			if(sWord == "TABLE"){
				sI++;
				if(isRelationName()){
					string relName=sToks[sI];
					sI++;
					if(sToks[sI] == "(" ){
						sI++;
						if(isTypedAttributeList()){
							//vector<TypedAttribute> typedAttrs = TypedAttributeList();
							if(sToks[sI]==")"){
								sI++;
								string tempP = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //TODO: IDEA: should we combine 'primary' and 'key' as they should never be apart?
								if(tempP=="PRIMARY"){
									sI++;
									string tempK = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
									if(tempK=="KEY"){
										sI++;
										if(sToks[sI]=="("){
											sI++;
											if(isAttributeList()){
												if(sToks[sI]==")"){
													sI++;
													isCmd=true;
													cout<<"xxx Well-formed 'CREATE' command on: "<<relName<<endl;;
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
			leave("CREATE");
		}
		
		//UPDATE dots SET x1 = 0 WHERE x1 < 0;
		//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
		else if(fWord=="UPDATE"){
			enter("UPDATE");
			sI++;
			if(isRelationName()){
				string relName=sToks[sI];
				sI++;
				if(sToks[sI]=="SET"){
					sI++;
					//loop look here
					if(isAttributeName()){
						string attrName=sToks[sI];
						sI++;
						if(sToks[sI]== "="){
							sI++;
							if(isLiteral()){
								//some looping needed 
								while(sToks[sI]==","){ cout<<"\n\n\nERROR, NO SUPPORT FOR MULTIPLE ATTRIBUTE-NAME ASSIGNMENTS YET\n\n\n"; return false; sI++;}
								sI++;
								if(sToks[sI]=="WHERE"){
									sI++;
									if(isCondition()){
										sI++;
										isCmd=true;
										cout<<"xxx Well-formed 'Update' command on: "<<relName<<endl;;
									}else{errOut("error in condition");}
								}else{errOut("expected \"WHERE\"");}
							}else{errOut("Error in literal");}						
						}else{errOut("Expected \"=\" after \"UPDATE "+relName+" SET "+attrName+"\"");}
					}else{errOut("Expected <attribute-name> after \"UPDATE "+relName+" SET \"");}
				}else{errOut("Expected \"SET\" after \"UPDATE "+relName+"\"");}
			}else{errOut("Expected relation-name after UPDATE");}
		}
		
		else if(fWord=="INSERT"){
		
		}
		
		else if(fWord=="DELETE" ){
		
		}
		
		else{isCmd=false;}
		if(!isCmd){sI=cmdSi;}
		return isCmd;
	}

	
	/*Non-terminal Functions:
	void query(); void relationName(); void identifier(); void alpha(); void digit(); void expr(); void atomicExpr(); void selection();
	void condition(); void conjunction(); void comparison(); void op(); void operand(); void attributeName(); void literal(); 
	void projection(); void attributeList(); void renaming(); void unionF(); void difference(); void product();  
	*/
	/*Non-terminal helpers:
	bool isDigit(string);
	bool isAlpha(string);
	*/
	/*Parser Specific Functions/Members:
	void getToke();
	Helper Funcs
	*/

	//Helper Funcs
	void errOut(string s) {
		cout<<"\n\n*** ERROR: "<<s<<endl<<endl;
	}
	void errorS(string s) {
	   cout<<"\n*** ERROR: "<<s<<endl;
	   exit(1);
	}

	void enter(string name) {
		spaces(level++);
		cout<<"+-"<<name<<": Enter, \t";
		cout<<"Tok == "<<sToks[sI]<<endl;
		//printf("+-%c: Enter, \t", name);
		//printf("Sym == %s\n", sym);
	}

	void leave(string name) {
		spaces(--level);
		cout<<"+-"<<name<<": Leave, \t";
		cout<<"Tok == "<<sToks[sI]<<endl;
		//printf("+-%c: Leave, \t", name);
		//printf("Sym == %c\n", sym);
	}

	void spaces(int local_level) {
		while (local_level-- > 0)
			cout<<"| ";
	}

	void getToke(){ //TODO: fix this repetition
		getSTok();
	}

	bool ParseQuery(){
		return query();
	}
	
	
	//query ::= relation-name <- expr ;
	bool query(){
		enter("Query");
		bool success = relationName();
		if(success){
			addPTok(sTok); //dbEng: This is the relation-name
			getSTok();
			success = sTok == "<";
			if(success){ //TODO: try if(success = sTok == "<")
				getSTok();
				success = sTok == "-";
				if(success){
					addPTok("<-");
					getSTok();
					success = expr();
					if(success){
						cout<<"***Successful Expression in Query\n"; //dbEng: This is where the successful expression returns...
					}else{errorS("Error in Expression");}
				}else{errorS("Expected \"-\""); }
			}else{errorS("Expected \"<\""); }
		}else{errorS("Invalid Relation Name");}
		success= sTok==";";
		if(success){
			addPTok(sTok);
			//getSTok(); //Do not getSTok at the end of a query!
		}else{errorS("Expected semi-colon after query");}
		leave("Query");
		return success;
	}

	//relation-name ::= identifier
	bool relationName(){
		enter("RelationName");
		bool isRel = identifier();
		leave("RelationName");
		return isRel;
	}
/*	bool isRelationName(){
		enter("RelationName");
		bool isRel = identifier();
		leave("RelationName");
		return isRel;
	}*/
	

	//identifier ::= alpha { ( alpha | digit ) }
	bool identifier(){
		bool isIdentifier=false;
		enter("Idenfitier");
		string identif = sTok;
		if(isalpha(identif[0]) || identif[0]=='_' ){
			isIdentifier=true;
			for(int i=1; i<identif.size(); i++){
				char c=identif[i];
				if( !(isalpha(c) || c=='_' || isdigit(c)) ){
					isIdentifier = false;
					break;
				}
			}
		}
		leave("Idenfitier");
		return isIdentifier;
	}
	

	//expr ::= atomic-expr | selection | projection | renaming | union | difference | product
	bool expr() {
		enter("Expression");
		if(atomicExpr()||selection()||projection()||renaming()||unionF()||difference()||product())
			return true;
		else
			return false;
	}
/*	bool expr() {
		enter("Expression");
		bool isExpr = projection();
		if(!isExpr){
			isExpr=selection();
			if(!isExpr){
				isExpr=product();
				if(!isExpr){
					isExpr=renaming();
					if(!isExpr){
						isExpr=unionF();
						if(!isExpr){
							isExpr=difference();
							if(!isExpr){
								isExpr=atomicExpr();
							}
						}
					}
				}
			}
		}
		leave("Expression");
		return isExpr;
	}*/

	//atomic-expr ::= relation-name | ( expr )
	bool atomicExpr(){ //TODO: PROBLEMS IN HERE!!!
		bool isAE = relationName();
		if(isAE){
			//addPTok(sTok); //add relation-name to parserTokens
			getSTok();
		}else{
			isAE = sTok=="(";
			if(isAE){
				addPTok(sTok); //add comma to parsertokens
				getSTok();
				isAE = expr();
				if(!isAE){
					errorS("expected expression within paren in atomic-expression");
					return isAE; //TODO: HACK: should not return in func like this...
				}
				isAE= sTok==")";
				if(isAE){
					addPTok(sTok);// add closing paren to parserTokens
					getSTok();
				}else{errorS("expected closing paren in atomic-expression");}
			}else{errorS("Error in atomic expression. atomic-exp is neither a relation nor an expression");}
		}
		return isAE;
	}

	//selection ::= select ( condition ) atomic-expr
	bool selection(){
		bool isSel = false;
		
		return isSel;
	}

	//condition ::= conjunction { || conjunction }
	bool condition(){
		bool isCond = false;
		enter("Condition");
		conjunction();
		if(sTok == "||"){
			getSTok();
			conjunction();
		}
		leave("Condition");
		return isCond;
	}

	//conjunction ::= comparison { && comparison }
	bool conjunction(){
		bool isConj = false;
		enter("Conjunction");
		comparison();
		while(sTok=="&&"){
			getSTok();
			comparison();
		}
		leave("Conjuction");
		return isConj;
	}

	//comparison ::= operand op operand | ( condition )
	bool comparison(){
		bool isComp = false;
		/* Old
		enter("Comparison");
		Operand();
		Op();
		Operand();
		if(sym=="|"){
			getsym();
			Condition();
		}
		leave("Comparison");
		*/
		enter("Comparison");
		if(sTok=="("){
			getSTok();//clear "("
			condition();
			if(sTok!=")"){
				errorS("expected closing paren"); 
			}
			getSTok();//clear ")"
		}else{
			operand();
			op();
			operand();
		}
		leave("Comparison");
		return isComp;
	}

	// op ::= {"==", "!=", "<" , ">", "<=", ">="}
	bool op(){
		bool isOp;
		if(sTok=="=="||sTok=="!="||sTok=="<"||sTok==">"||sTok=="<="||sTok==">=")
			isOp = true;		
		else					//We only use six possible opperators and use this if statement	
			isOp = false;		//to determine if the token is a valid opperator.			
	}	

/*	//enum opEnum {"=="=0, "!=", "<" , ">", "<=", ">="}
	bool op(){
		bool isOp = false;
		if(sTok == "=="){
		
		
		}else if(sTok == "!="){
		
		}else if(sTok == "<"){
		
		}else if(sTok == ">"){
		
		}else if(sTok == "<="){
		
		}else if(sTok == ">="){
		
		}else{
			//Not an 'op'
		}
		return isOp;
	}replaced with the code above */ 

	//operand ::= attribute-name | literal
	bool operand(){
		bool isOperand = false;
		return isOperand;
	}

	// literal ::= intentionally left unspecified
	bool literal(){
		bool isLiteral = false;
		//... require futher clarification
		return isLiteral;
	}

	// projection ::= project ( attribute-list ) atomic-expr
	bool projection(){
		enter("Projection");
		bool isProject = sTok=="project";
		if(isProject){
			addPTok(sTok);
			getSTok();
			if(sTok == "(" ){ //Question: should this be an if, since there can only be 1 attribute-list?
				addPTok(sTok);
				getSTok(); 
				isProject = attributeList();
				if(!isProject){
					errorS("Error parsing attribute-list");
					return isProject; //TODO: should not return in middle of func like this...
				}
				isProject = sTok == ")";
				if(!isProject){
					errorS("Expected closing paren after attribute-list");
					return isProject; //TODO: should not return in middle of func like this...
				}
				addPTok(sTok);
				getSTok(); //clear ")"
			}		
			isProject = atomicExpr();
		}
		leave("Projection");
		return isProject;
	}

	// attribute-list ::= attribute-name { , attribute-name } 
	bool attributeList(){
		enter("AttributeList");
		bool isAttribList = attributeName();
		if(isAttribList){
			addPTok(sTok); //add first attribute-name to parserTokens
			getSTok(); 
		}
		while(sTok==","){
			addPTok(sTok); // add comma to parser tokens
			getSTok();
			isAttribList = attributeName();
			if(!isAttribList){
				errorS("Error while parsing attribute-list, attribute name was not as expected");
				break;
			}else{
				addPTok(sTok); // add next attribute-name to parserTokens
				getSTok();
			}
		}
		leave("AttributeList");
		return isAttribList;
	}
	
	// attribute-name ::= identifier
	bool attributeName(){
		enter("AttributeName");
		bool isAttrib = identifier();
		if(isAttrib){
			
		}
		leave("AttributeName");
		return isAttrib;
	}

	// renaming ::= rename ( attribute-list ) atomic-expr
	bool renaming(){
		bool isRenaming = false;
		enter("Renaming");
		if(sTok == "rename"){
			while(sTok == "(" ){
				getSTok(); //clear "("
				attributeList();
				if(sTok != ")" ){
					errorS("Expected closing paren");
				} getSTok(); //clear ")"
			}
			atomicExpr();
		}
		leave("Renaming");
		return isRenaming;
	}

	// union ::= atomic-expr + atomic-expr
	bool unionF(){
		bool isUnionF = false;
		enter("Union");
		atomicExpr();
		if(sTok == "+" ){
			getSTok(); //clear "+"
		}else{ //errorS("Expected +"); 
		}
		atomicExpr();
		leave("Union");
		return isUnionF;
	}

	// difference ::= atomic-expr - atomic-expr
	bool difference(){
		bool isDiff = false;
		enter("Difference");
		atomicExpr();
		if(sTok == "-" ){
			getSTok(); //clear "-"
		}else{ errorS("Expected -"); }
		atomicExpr();
		leave("Difference");
		return isDiff;
	}

	// product ::= atomic-expr * atomic-expr 
	bool product(){
		enter("Product");
		bool isProd = atomicExpr();
		cout<<"DEBUG: isProd:"<<isProd<<endl;
		if(isProd){
			
			//addPTok(sTok
			isProd= pTokens[sTokI+1]=="*";
			cout<<"DEBUG: isProd:"<<isProd<<endl;
			if(sTok == "*" ){
				getSTok(); //clear "*"
			}else{ 
				
				//errorS("Expected *"); 
			}
			atomicExpr();
		}	
		cout<<"DEBUG: isProd:"<<isProd<<endl;
		leave("Product");
		return isProd;
	}
	
	};

int main(){
	cout<<"-Starting Parser Main\n";
	Parser* myP = new Parser("parser_milestone_good_inputs.txt");
	cout<<"-Exiting Parser Main\n";
	cout << "Press ENTER to quit";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return 0;
}

