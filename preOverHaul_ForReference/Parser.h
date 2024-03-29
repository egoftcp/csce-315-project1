/* parser.cpp:
 */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include<boost/tokenizer.hpp>

using namespace std;


class Parser{
public:
	bool allowNonCaps; //True = allow mixed-case Command keywords (i.e. SELECT vs sElecT)
	bool haltBetween; //True = halt execution after each Query/Command is parsed 
	int debug; 	/*Debug Levels
	0-No Output
	1-Minimal pass/fail output
	2-More pass/fail info
	3-Show syntax error messages,
	4-Show enter/leave print statements */

	//Constructor
	Parser(int Debug=1, bool HaltBetweenExec=false, bool AllowNonCapitalCMDs=false) :
		debug(Debug),
		haltBetween(HaltBetweenExec),
		allowNonCaps(AllowNonCapitalCMDs)
	{ ; }
	
	//Runs Parser On Single or Multiple Command/Queries
	//Returns number of failed statements or -1 for system error
	int ParseProgramBlock(string Program){
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
			if(haltBetween){
				cout << "Press ENTER to continue";
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout<<endl<<endl;
			}
		}
		return failCount;

	}
	
	//Runs Parser on all Command/Queries in a text file (useful for testing)
	//Assumes (textfile will be newLine seperated) AND (file will NOT have <cr><lf> line endings)
	//Returns number of failed statements or -1 for input-file error
	int ParseTxtFile(string fileName){
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
			if(!ParseSingleLine(line)){
				failCount++;
			}
			if(haltBetween){
				cout << "Press ENTER to continue";
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout<<endl<<endl;
			}
		}
		return failCount;
	}
	
	vector<string> getTokens(string line){
		return dbTokens(line);
	}
	
private:
	vector<string> sToks;
	int sI;
	int level;
	/* token consumption information
	"primitive" functions which consume all of their input:
	isLiteral();
	isIdentifier();
	isInteger();

	Additionally all terminal/special tokens (i.e. '(' , '||' , ',' , 'SELECT' , etc ) will be comsumed in the highest level non-terminal function in which they appear 

	//isType() is a good example. it must consume all tokens EXCEPT for <integer> if it is a VARCHAR
	*/

	void resetParserVals(){
		sToks.clear();
		sI=0;
		level=0;
	}
	void printSTok(){
		//cout<<"*******Scanner Tokens:\n";
		for(vector<string>::iterator it=sToks.begin(); it!=sToks.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
	string retUpper(string inStr){
		string upp = inStr;
		for(string::iterator it = upp.begin(); it!=upp.end(); ++it){
			*it = std::toupper((unsigned char)(*it));
		}
		return upp;
}

	//Scanner
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

	bool ParseSingleLine(string line){
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
	bool ParseTokens(){
		bool passedParse;
		if(isFCommand()){
			passedParse = isCommand();
		}else{
			passedParse = isQuery();
		}
		return passedParse;
	}
	
	//Grammar Functions:
	bool isAtomicExpr(){
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
	bool isQuery(){
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
		leave("isQuery");
		return isQ;
	}
	bool isSelection(){
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
	bool isProjection(){
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
	bool isRenaming(){
	// renaming ::= rename ( attribute-list ) atomic-expr
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
	bool isUnion(){
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
	bool isProduct(){
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
	bool isDifference(){
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
	bool isExpr() {
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
	bool isRelationName(){
	//relation-name ::= identifier
		enter("isRelationName");
		bool isRel = isIdentifier();
		leave("isRelationName");
		return isRel;
	}
	bool isIdentifier(){
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
	bool isAttributeList(){
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
	bool isAttributeName(){
	//attribute-name ::= identifier
		enter("isAttributeName");
		bool isAttrib = false;
		isAttrib = isIdentifier();
		leave("isAttributeName");
		return isAttrib;
	}
	bool isType(){
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
	bool isInteger(){
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
	bool isLiteral(){
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
	bool isTypedAttributeList(){
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
	bool isCondition(){
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
	bool isConjunction(){
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
	bool isComparison(){
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
	bool isOp(){
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
	bool isOperand(){
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
	bool isFCommand(){ 
	//Determines if first token matches a Command
		string f = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
		return ( (f=="OPEN") || (f=="CLOSE") || (f=="WRITE") || (f=="EXIT") || (f=="SHOW") || (f=="CREATE") || (f=="UPDATE") || (f=="INSERT") || (f=="DELETE") );
	}
	bool isCommand(){
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
	bool isOpen(){
	//open-cmd ::== OPEN relation-name
		enter("isOpen");
		bool isOpn=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
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
	bool isClose(){
	//close-cmd ::== CLOSE relation-name
		enter("isClose");
		bool isCls=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
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
	bool isWrite(){
	//write-cmd ::== WRITE relation-name
		enter("isWrite");
		bool isWrt=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);	
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
	bool isExit(){
	//exit-cmd ::== EXIT
		enter("isExit");
		bool isExt=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
		if(sToks[sI]=="EXIT"){
			sI++;
			isExt=true;
		}
		leave("isExit");
		return isExt;
	}
	bool isShow(){
	//show-cmd ::== SHOW atomic-expr
		enter("isShow");
		bool isShw=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
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
	bool isCreate(){
	//create-cmd ::= CREATE TABLE relation-name ( typed-attribute-list ) PRIMARY KEY ( attribute-list )
		enter("isCreate");
		bool isCrt=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
		if(sToks[sI]=="CREATE"){
			sI++;
			sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
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
	bool isUpdate(){
	//update-cmd ::= UPDATE relation-name SET attribute-name = literal { , attribute-name = literal } WHERE condition
		enter("isUpdate");
		bool isUpd=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
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
	bool isInsert(){
	// insert-cmd ::= INSERT INTO relation-name VALUES FROM ( literal { , literal } ) 
				//  | INSERT INTO relation-name VALUES FROM RELATION expr
		enter("isInsert");
		bool isIns=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
		if(sToks[sI]=="INSERT"){
			sI++;
			sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'INTO'
			if(sToks[sI]=="INTO"){
				sI++;
				if(isRelationName()){
					sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'VALUES'
					if(sToks[sI]=="VALUES"){
						sI++;
						sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'FROM'
						if(sToks[sI] =="FROM"){
							sI++;
							string temp= (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for !!possible!! 'RELATION' token
							if(temp=="RELATION"){
								//This is < VALUES FROM RELATION expr > case of 'INSERT'
								sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'RELATION' token
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
	bool isDelete(){
	//delete-cmd ::= DELETE FROM relation-name WHERE condition
		enter("isDelete");
		bool isDel=false;
		sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]);
		if(sToks[sI]=="DELETE"){
			sI++;
			sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'FROM'
			if(sToks[sI]=="FROM"){
				sI++;
				if(isRelationName()){
					sToks[sI] = (allowNonCaps?retUpper(sToks[sI]):sToks[sI]); //mixed-case consideration for 'WHERE'
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
	void errOut(string s) {
		if(debug>2){
			cout<<"\n*** ERROR: "<<s<<endl;
		}	
	}
	void enter(string name) {
		if(debug>3){
			spaces(level++);
			cout<<"+-"<<name<<": Enter, \t";
			cout<<"Tok == "<<sToks[sI]<<endl;
		}
	}
	void leave(string name) {
		if(debug>3){
			spaces(--level);
			cout<<"+-"<<name<<": Leave, \t";
			cout<<"Tok == "<<sToks[sI]<<endl;
		}
	}
	void spaces(int local_level) {
		if(debug>3){
			while (local_level-- > 0) {cout<<"| ";}
		}
	}
};

/*
int main(){
	Parser myP(2,true,true);
	string sampleProg="SHOW set_diff_test; rename_test <- rename (v_fname, v_lname, v_personality, v_bounty) enemies  ; INSERT INTO lifeforms VALUES FROM (\"Martian\", \"Mars\"); UPDATE dots SET x1 = 0 WHERE x1 < 0; INSERT INTO dots VALUES FROM (-1, 0, 20);";
	string sampleSingle="advanced_query <-       project  (x   )  (select (   y == y2) ( points   * dots_to_points));";
	string txtFileName = "parser_milestone_good_inputs.txt";
	
	
	cout<<"Parser can be called with a with a single Query/Command, a Program Block, or even be passed a text file to read from.\n";
	cout<<"Additionally, the parser allows for some level of customization.\n";
	cout<<"*The caller can choose to enforce all uppercase commands (such as SELECT) or allow for mix-case.\n";
	cout<<"*The caller can enable the parser to pause (wait for enter key) between parses, so the caller may examine the results.\n";
	cout<<"*The caller may also specify different levels of verbosity (debug argument) from silent(0) to extra-verbose(4).\n";
	cout<<"***Note: If caller is interfacing code with parser, be sure to set Debug=0; and HaltBetweenExec=false;\n\n";
	cout<<"So let's pass a single Command to be parsed!\nPress ENTER to continue\n"; cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	int result = myP.ParseProgramBlock(sampleSingle);
	cout<<(result==0?"Nice Job, Single Query Parsed!":"Boo, sample single line failed")<<endl<<endl;
	
	
	cout<<"Now lets parse a block of Commands from a single string...\nPress ENTER to continue\n"; cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	result = myP.ParseProgramBlock(sampleProg);
	if(result==-1){
		cout<<"Unknown Error"<<endl;
	}else{
		cout<<"Number of Failed Statements: "<<result<<endl;
	}
	
	cout<<"You can also pass parser a textfile to read Commands from. Check out the parser main to see how!\n\n\n";
	//result = myP.ParseTxtFile(txtFileName);
	//if(result==-1){
	//	cout<<"Error Opening input file"<<endl;
	//}else{
	//	cout<<"\n\nNumber of Failed Statements: "<<result<<endl;
	//}
	
	Parser par(0,false,true);
	string usrCmd="";
	cout<<"Neat! Wanna try some commands? When you get bored, just enter 'leave' to exit.\n\n";
	while(1){
		cout<<"::";
		cin>>usrCmd;
		cout<<"~"<<usrCmd<<endl;
		if(usrCmd=="leave"){break;}
		int fail = par.ParseProgramBlock(usrCmd);
		cout<<"~"<<(fail==0?"PASSED":"FAILED")<<endl;
	}
		
	cout<<"\n\nThanks and gigem!"<<endl<<endl;
	cout<<"Exiting...\n";
	return 0;
}

*/



