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

class Parser{
private:
	vector<string> sTokens; //ScannerTokens  i.e. [dog] [<] [-] ... ["] [joe] [bob] ... [;]
	vector<string> pTokens; //Completed Parser Tokens i.e. [dog] [<-] ... ["] [joe bob] ["] ... [;]  //perhaps no special chars like [<-] and ["] ?
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
	
	void getSTok(){
		sTokI++;
		sTok = sTokens[sTokI];
	}
	
public:
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
			cout<<"******************************\n**Handling Line: "<<line<<endl;
			//Get Tokens
			vector<string> toks = tokenizeLine(line);
			//Print Tokens
			cout<<"**Scanner Tokens: ";
			for(vector<string>::iterator it=toks.begin(); it!=toks.end(); ++it){
				cout<<"["<<(*it)<<"] ";
			}cout<<endl;
			
			//Parse
			if(isCommand(toks[0])){
				cout<<"Need To implement Command Parsing.. Skipping\n";
			}else{
				sTokens = toks;
				//sTokI = 0;
				sTok= sTokens[0];
				ParseQuery();
				cout<<"***Query Parsed Successfully:\n";
				printPTok();
			}
						
			cout<<"**Done handling line\n****************************\n\n";
			cout << "Press ENTER to continue";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	
	vector<string> tokenizeLine(string line){
		vector<string> tokens;
		boost::char_separator<char> separator(" \n","\"()+<>=-;,");
		boost::tokenizer< boost::char_separator<char> > tok( (std::string::const_iterator)line.begin(), (std::string::const_iterator)line.end(), separator);
		for(boost::tokenizer< boost::char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end(); ++beg){
		   tokens.push_back( *beg );
		}
		return tokens;
	}
	
	void lex(vector<string> tokens){
		while(1){
			;
		}		
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
	
	/*Old Funcs
	void handleProgram(string prog){
		cout<<"*******\nSOMEONE CALLED handleProgram\n********\n";
	
		vector<string> Lines;
		stringstream iss(prog);
		
		string ln="";
		while(iss.good()){
			char c;
			iss>>c;
			ln+=c;
			if(c==';'){
				Lines.push_back(ln);
				cout<<"added line: "<<ln<<endl;
				ln="";
			}
		}
			// cout<<"read line# "<<i<<endl;
			
			// int maxLineSize=1020;
			// char buff[maxLineSize];
			// string ln;
			
			// iss.get(buff,maxLineSize,';');
			// getline(iss, ln, ':');
			// cout<<"read:"<<iss.gcount()<<" chars"<<endl;
			
			// string newLn(buff);
			// cout<<"adding newLine: "<<ln<<endl;
			// Lines.push_back(ln);
				
			//cout<<"done breaking apart program..."<<endl;
		
		for(vector<string>::iterator it=Lines.begin(); it!=Lines.end(); ++it){
			cout<<"calling handle CorQ on string: "<<(*it)<<endl;
			//handleCorQ(*it);
		}
		
	}
	
	bool handleQuery(string Query){
		cout<<"Handeling a query!!!!!\n"<<Query<<endl;
		return true;
	}
		
	bool handleCommand(string Cmd){
		stringstream iss(Cmd);
		string fWord;
		iss>>fWord;
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
	*/
	
private:	
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

