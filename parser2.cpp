/* parse.c: simple parser -- no output
 * grammar:
 *  expression = ["+"|"-"] term {("+"|"-”) term} .
 *	term = factor {("*"|"/”) factor}
 *	factor = ident | number | "(" expression ")”'
 * Motivation & more examples at: http://www.cs.utsa.edu/~wagner/CS3723/rdparse/rdparser.html, http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
 * See txt file for some sample runs.
 * 
 * This program is to demonstrate recursive descent parsing. It expects input
 * expressions at > followed by DOT(.). Look at slides (pg 7) for grammar. Exit
 * safely with Ctrl-C. In case input expression does not meet grammar, the
 * program generates Error and exits. 
 * Feel free to point out errors if any (and fixes!) to 
 * aalap[AT]cse[DOT]tamu[DOT]edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
//#include <deque>
#include <vector>
#include<boost/tokenizer.hpp>

using namespace std;


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
	
	void printPTok(){
		cout<<"**Parser Tokens: ";
		for(vector<string>::iterator it=pTokens.begin(); it!=pTokens.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
	
	void printSTok(){
		cout<<"**Scanner Tokens: ";
		for(vector<string>::iterator it=sTokens.begin(); it!=sTokens.end(); ++it){
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
		ifstream inFile( fileName.c_str() );
		//Need to put in loop, splitting prog on '\n' or ';' , then handle each CorQ
		while(inFile.good() ){ //assuming infile will be newLine seperated
			sTokens.clear();
			pTokens.clear();
			sTokI=0;
			sTok="";
			level=0;
			string line;
			getline(inFile, line);	//function in/of <string> lib
			if(line==""){continue;} //Skip blank Lines
			cout<<"\n\n******************************\n**Handling Line: "<<line<<endl;
			
			//Get Tokens
			sTokens = dbTokens(line);
			sTok= sTokens[0];
			
			//Print Tokens
			printSTok();
			
			//Parse
			bool passedParse = ParseTokens();
			
			cout<<"\n\n"<< (passedParse?"PASSED":"FAILED") << "on:\n";
			cout<<"\n\nInputLine:"<<line<<endl;
			cout<<"**Done handling line\n****************************\n";
			cout << "Press ENTER to continue";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	bool ParseTokens(){
		bool passedParse;
		if(isCommand(sTok)){
			passedParse = isCommand();
			cout<<"Need To implement Command Parsing.. Skipping\n";
		}else{
			passedParse = ParseQuery();
		}
		return passedParse;
	}
	
	bool isCommand(string fWord){
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
	void errorS(string s) {
	   cout<<"\n*** ERROR: "<<s<<endl;;
	   exit(1);
	}
	void enter(string name) {
		spaces(level++);
		cout<<"+-"<<name<<": Enter, \t";
		cout<<"Tok == "<<sTok<<endl;
		//printf("+-%c: Enter, \t", name);
		//printf("Sym == %s\n", sym);
	}
	void leave(string name) {
		spaces(--level);
		cout<<"+-"<<name<<": Leave, \t";
		cout<<"Tok == "<<sTok<<endl;
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

	void ParseQuery(){
		query();
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

	/*Old digit/alpha stuff
	//alpha ::= a | … | z | A | … | Z | _
	void alpha(){

	}
	
	//alpha ::= a | … | z | A | … | Z | _
	bool isAlpha(char c){
		
	}
	
	//digit ::= 0 | … | 9
	bool isDigit(char c){
		
	}
	

	//digit ::= 0 | … | 9
	void digit(){

	}
	bool isDigit(Token t){
		try{
			int dig = atoi(t); 
			if(dig<10 && dig>=0){
				return true;	
			}
		}
		catch(e){ return false; }
		return false;
	}
	*/

	//expr ::= atomic-expr | selection | projection | renaming | union | difference | product
	bool expr() {
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

	//enum opEnum {"=="=0, "!=", "<" , ">", "<=", ">="}
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
	}

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

int main() {
	cout<<"-Starting Parser Main\n";
	Parser* myP = new Parser("parser_milestone_good_inputs.txt");
	cout<<"-Exiting Parser Main\n";
	
	return 0;
}

