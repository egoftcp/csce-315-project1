#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>
#include <limits>
#include <time.h>
#include <vector>
#include <boost/tokenizer.hpp>
//#include "ParserEngine.h"
//#include "DataType.h"
//#include "Attribute.h"
//#include "Relation.h"
//#include "DBEngine.h"
//#include "DBMS.cpp"

using namespace std;
vector<string> sToks;
//DBMS exDBMS1(false, 0, "./"); 

//Formating functions
void white(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<print;//simply takes a string to print and ensures it is white font
}  
void green(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	cout<<print;//simply takes a string to print and ensures it is green font
}
void centerstring(char* s)
{
   int l=strlen(s);
   int pos=(int)((80-l)/2);
   for(int i=0;i<pos;i++)
    white(" ");	//adds an appropriate amount of spaces before the passed string so that it 
   cout<<s;		//centers on a normal 80 character wide console
}
void title(char* currentTitle){
	system("cls");
	for(int i=0;i<80;i++)
		green("*");
	centerstring(currentTitle);
	cout<<endl;
	for(int i=0;i<80;i++)
		green("*");
}
/*	void printSTok(){
		//cout<<"*******Scanner Tokens:\n";
		for(vector<string>::iterator it=sToks.begin(); it!=sToks.end(); ++it){
			cout<<"["<<(*it)<<"] ";
		}cout<<endl;
	}
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
	}*/
//Root Menus
string primaryMenu(){
	int selection=NULL;
	cin.clear();
	title("DVD Database Management System");
	green("*");white("(1)");green("Customers");cout<<endl;
	green("*\tAdd new customer");cout<<endl;
	green("*\tRemove customer");cout<<endl;
	green("*\tUpdate customer");cout<<endl;
	green("*\tList customer");cout<<endl;
	green("*\tSearch customer");cout<<endl;
	green("*");white("(2)");green("DVDs");cout<<endl;
	green("*\tAdd new DVD");cout<<endl;
	green("*\tRemove DVD");cout<<endl;
	green("*\tUpdate DVD");cout<<endl;
	green("*\tList DVD");cout<<endl;
	green("*\tSearch DVD");cout<<endl;
	green("*\tList customers by DVD");cout<<endl;
	green("*");white("(3)");green("Rentals");cout<<endl;
	green("*\tSearch available DVDs");cout<<endl;
	green("*\tCheck out DVD");cout<<endl;
	green("*\tCheck in DVD");cout<<endl;
	green("*\tList rentals by customer");cout<<endl;
	green("*Options ");white("(1)");green(", ");white("(2)");green(", ");green("or ");white("(3)");green(":");cin>>selection;
	if(selection==1)return "customerMenu";
	else if(selection==2)return "dvdMenu";
	else if(selection==3)return "rentalMenu";
	else if(selection==0)return "close application";
	else return "primaryMenu";
}
string customerMenu(){
	int selection=NULL;
	title("Customer Menu");
	green("*   Customers");cout<<endl;
	green("*");white("\t(1)");green("Add new customer");cout<<endl;
	green("*");white("\t(2)");green("Remove customer");cout<<endl;
	green("*");white("\t(3)");green("Update customer");cout<<endl;
	green("*");white("\t(4)");green("List customer");cout<<endl;
	green("*");white("\t(5)");green("Search customer");cout<<endl;
	green("*");white("(6)");green("DVDs");cout<<endl;
	green("*\tAdd new DVD");cout<<endl;
	green("*\tRemove DVD");cout<<endl;
	green("*\tUpdate DVD");cout<<endl;
	green("*\tList DVD");cout<<endl;
	green("*\tSearch DVD");cout<<endl;
	green("*\tList customers by DVD");cout<<endl;
	green("*");white("(7)");green("Rentals");cout<<endl;
	green("*\tSearch available DVDs");cout<<endl;
	green("*\tCheck out DVD");cout<<endl;
	green("*\tCheck in DVD");cout<<endl;
	green("*\tList rentals by customer");cout<<endl;
		green("*Options ");white("1");green("-");white("7");green(":");cin>>selection;
	if(selection==1)return "addNewCustomer";
	else if(selection==2)return "removeCustomer";
	else if(selection==3)return "updateCustomer";
	else if(selection==4)return "listCustomer";
	else if(selection==5)return "searchCustomer";
	else if(selection==6)return "dvdMenu";
	else if(selection==7)return "rentalMenu";
	else if(selection==0)return "close application";
	else return "primaryMenu";
}
string dvdMenu(){
	int selection=NULL;
	title("DVD Menu");
	green("*");white("(1)");green("Customers");cout<<endl;
	green("*\tAdd new customer");cout<<endl;
	green("*\tRemove customer");cout<<endl;
	green("*\tUpdate customer");cout<<endl;
	green("*\tList customer");cout<<endl;
	green("*\tSearch customer");cout<<endl;
	green("*   DVDs");cout<<endl;
	green("*");white("\t(2)");green("Add new DVD");cout<<endl;
	green("*");white("\t(3)");green("Remove DVD");cout<<endl;
	green("*");white("\t(4)");green("Update DVD");cout<<endl;
	green("*");white("\t(5)");green("List DVD");cout<<endl;
	green("*");white("\t(6)");green("Search DVD");cout<<endl;
	green("*");white("\t(7)");green("List customers by DVD");cout<<endl;
	green("*");white("(8)");green("Rentals");cout<<endl;
	green("*\tSearch available DVDs");cout<<endl;
	green("*\tCheck out DVD");cout<<endl;
	green("*\tCheck in DVD");cout<<endl;
	green("*\tList rentals by customer");cout<<endl;
	green("*Options ");white("1");green("-");white("8");green(":");cin>>selection;
	if(selection==1)return "customerMenu";
	else if(selection==2)return "addNewDvd";
	else if(selection==3)return "removeDvd";
	else if(selection==4)return "updateDvd";
	else if(selection==5)return "listDvd";
	else if(selection==6)return "searchDvd";
	else if(selection==7)return "listCustomersByDvd";
	else if(selection==8)return "rentalMenu";
	else if(selection==0)return "close application";
	else return "primaryMenu";
}
string rentalMenu(){
	int selection=NULL;
	title("Rental Menu");
	green("*");white("(1)");green("Customers");cout<<endl;
	green("*\tAdd new customer");cout<<endl;
	green("*\tRemove customer");cout<<endl;
	green("*\tUpdate customer");cout<<endl;
	green("*\tList customer");cout<<endl;
	green("*\tSearch customer");cout<<endl;
	green("*");white("(2)");green("DVDs");cout<<endl;
	green("*\tAdd new DVD");cout<<endl;
	green("*\tRemove DVD");cout<<endl;
	green("*\tUpdate DVD");cout<<endl;
	green("*\tList DVD");cout<<endl;
	green("*\tSearch DVD");cout<<endl;
	green("*\tList customers by DVD");cout<<endl;
	green("* Rentals");cout<<endl;
	green("*");white("\t(3)");green("Search available DVDs");cout<<endl;
	green("*");white("\t(4)");green("Check out DVD");cout<<endl;
	green("*");white("\t(5)");green("Check in DVD");cout<<endl;
	green("*");white("\t(6)");green("List rentals by customer");cout<<endl;
		green("*Options ");white("(1)");green("-");white("(6)");green(":");cin>>selection;
	if(selection==1)return "customerMenu";
	else if(selection==2)return "dvdMenu";
	else if(selection==3)return "searchAvailableDvd";
	else if(selection==4)return "checkOutDvd";
	else if(selection==5)return "checkInDvd";
	else if(selection==6)return "listRentalsByCustomer";
	else if(selection==0)return "close application";
	else return "primaryMenu";
}
//Database Command Menus
string addNewCustomerMenu(){
	time_t seconds = time(NULL);
	int selection=NULL;
	string userId,firstName,lastName,phoneNumber;
	char id[21],choice;
	itoa(seconds,id,10);
	title("Add New Customer");
	green("*Enter Customer's First Name:");white("");cin>>firstName;
	green("*Enter Customer's Last Name:");white("");cin>>lastName;
	green("*Enter Customer's Phone Number:");white("");cin>>phoneNumber;
	userId=firstName.substr(0,3)+lastName.substr(0,3)+id[4]+id[5]+id[7]+id[8]+id[9];
	green("*Customer's user ID will be:");white("");cout<<userId<<endl;
	green("*");white("1");green(" to accept above information, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+",\""+phoneNumber+"\");");white("");//printSTok();
		//exeDBMS1.Execute("INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+","+phoneNumber+");");
		system("pause");
	}
	else if(choice=='5')
		return "addNewCustomerMenu";
	else
		return "customerMenu";
	return "primaryMenu";
}
string removeCustomerMenu(){
	int selection=NULL;
	string userId,firstName="fNamenotImplemented",lastName="lNamenotImplemented",phoneNumber="phone#notImplemented",idToDelete;
	char choice;
	title("Remove Customer");
	green("*Enter Customer's User ID:");white("");cin>>idToDelete;
	white("");green("customerToDelete <- select (userId = "+idToDelete+") customers;");white("");//printSTok();
	//exeDBMS1.Execute("customerToDelete <- select (userId = "+idToDelete+") customers;");
	//exeDBMS1.Execute("SHOW customerToDelete;");
	cout<<idToDelete<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	green("*");white("1");green(" to Remove the above customer, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("");green("DELETE FROM customers WHERE (userId = "+idToDelete+");");white("");//printSTok();
		//exeDBMS1.Execute("DELETE FROM customers WHERE (userId = "+idToDelete+");");
		system("pause");
	}
	else if(choice=='5')
		return "removeCustomerMenu";
	else
		return "customerMenu";
	return "primaryMenu";
}
string updateCustomerMenu(){
	int selection=NULL;
	string userId,firstName="fNamenotImplemented",lastName="lNamenotImplemented",phoneNumber="phone#notImplemented",idToUpdate;
	char choice;
	title("Update Customer");green("*Enter Customer's User ID:");white("");cin>>idToUpdate;
	white("");green("customerToUpdate <- select (userId = "+idToUpdate+") customers;");white("");//printSTok();
	white("");green("SHOW customerToUpdate;");white("");//printSTok();
	//exeDBMS1.Execute("customerToUpdate <- select (userId = "+idToUpdate+") customers;");
	//exeDBMS1.Execute("SHOW customerToUpdate;");
	cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	green("*");white("1");green(" to update the customer, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("*");white("(1)");green("Change First Name");cout<<endl;
		green("*");white("(2)");green("Change Last Name");cout<<endl;
		green("*");white("(3)");green("Change Phone NUmber");cout<<endl;
	}
	else if(choice=='5')
		return updateCustomerMenu();
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='3');
	if(choice=='1'){
		green("*Enter Customer's First Name:");white("");cin>>firstName;
		green("*UPDATE customers SET firstName = "+firstName+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//exeDBMS1.Execute("UPDATE customers SET lastName = "+firstName+" WHERE userId = "+idToUpdate+";");
		//exeDBMS1.Execute("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		green("*Enter Customer's Last Name:");white("");cin>>lastName;
		white("*UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//exeDBMS1.Execute("UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";");
		//exeDBMS1.Execute("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		green("*Enter Customer's Phone Number:");white("");cin>>phoneNumber;
		white("*UPDATE customers SET phoneNumber = "+phoneNumber+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//exeDBMS1.Execute("UPDATE customers SET phoneNumber = "+phoneNumber+" WHERE userId = "+idToUpdate+";");
		//exeDBMS1.Execute("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else
		return "customerMenu";
	system("pause");
	return "primaryMenu";
}
string listCustomerMenu(){
	int selection=NULL;
	string userId="userId",firstName="fName",lastName="lName",phoneNumber="phone#";
	char choice;
	title("List Customers");
	green("*");white("(1)");green("List customers by User ID");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		//exeDBMS1.Execute("SHOW customers;");
		white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
		system("pause");
	}else if(choice=='5');
		return "customerMenu";
	return "primaryMenu";
}
string searchCustomerMenu(){
	int selection=NULL;
	string userId="userId",firstName="fName",lastName="lName",phoneNumber="phone#";	char choice;
	title("Search Customers");
	green("*");white("(1)");green("Search by First Name");cout<<endl;
	green("*");white("(2)");green("Search by Last Name");cout<<endl;
	green("*");white("(3)");green("Search by Phone NUmber");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Go back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='3'&&choice!='5');
	if(choice=='1'){
		green("*Enter First Name to search for:");white("");cin>>firstName;
		green("*searchByFirstName <- select (firstName = "+firstName+") customers;");cout<<endl;
		//exeDBMS1.Execute("searchByFirstName <- select (firstName = "+firstName+") customers;");
		//exeDBMS1.Execute("SHOW searchByFirstName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		green("*Enter Last Name to search for:");white("");cin>>lastName;
		green("*searchByFirstName <- select (lastName = "+lastName+") customers;");cout<<endl;
		//exeDBMS1.Execute("searchByFirstName <- select (lastName = "+lastName+") customers;");
		//exeDBMS1.Execute("SHOW searchByLastName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		green("*Enter Phone Number to search for:");white("");cin>>phoneNumber;
		green("*searchByFirstName <- select (phoneNumber = "+phoneNumber+") customers;");cout<<endl;
		//exeDBMS1.Execute("searchByPhoneNumber <- select (phoneNumber = "+phoneNumber+") customers;");
		//exeDBMS1.Execute("SHOW searchByPhoneNumber;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='5')
		return "customerMenu";
	system("pause");
	return "primaryMenu";
}
string addNewDvdMenu(){
	int selection=NULL;
	string inventoryNumber,dvdId,dvdTitle;
	char choice;
	title("Add New DVD");
	green("*Enter DVD ID:");white("");cin>>dvdId;
	green("*Enter DVD Title:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
	green("*Enter Inventory Number:");white("");cin>>inventoryNumber;
	green("*");white("1");green(" to accept above information, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("");green("INSERT INTO dvds VALUES FROM ("+inventoryNumber+","+dvdId+",\""+dvdTitle+"\");");cout<<endl;
		//exeDBMS1.Execute("INSERT INTO dvds VALUES FROM ("+inventoryNumber+","+dvdId+",\""+title+"\");");
		system("pause");
	}
	else if(choice=='5')
		return "addNewDvdMenu";
	else
		return "dvdMenu";
	return "primaryMenu";
}
string removeDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented",idToDelete;	char choice;
	title("Remove DVD");
	green("*Enter DVD ID to remove:");white("");cin>>idToDelete;
	white("dvdToDelete <- select (dvdId = "+idToDelete+") dvds;");cout<<endl;
	//exeDBMS1.Execute("dvdToDelete <- select (dvdId = "+idToDelete+") dvds;");
	//exeDBMS1.Execute("SHOW dvdToDelete;");
	cout<<idToDelete<<", "+inventoryNumber+", "+dvdTitle<<endl;
	green("*");white("1");green(" to Remove the above DVD, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("DELETE FROM dvds WHERE (dvdId = "+idToDelete+");");cout<<endl;
		//exeDBMS1.Execute("DELETE FROM dvds WHERE (dvdId = "+idToDelete+");");
		system("pause");
	}
	else if(choice=='5')
		return "removeDvdMenu";
	else
		return "customerMenu";
	return "primaryMenu";
}
string updateDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented",idToUpdate;
	char choice;
	title("Update DVD");
	green("*Enter DVD ID:");white("");cin>>idToUpdate;
	green("*dvdToUpdate <- select (userId = "+idToUpdate+") dvds;");cout<<endl;
	//exeDBMS1.Execute("dvdToUpdate <- select (dvdId = "+idToUpdate+") dvds;");
	//exeDBMS1.Execute("SHOW dvdToUpdate;");
	cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	green("*");white("1");green(" to Update the DVD, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("*");white("(1)");green("Change Inventory Number");cout<<endl;
		green("*");white("(2)");green("Change DVD Title");cout<<endl;
		green("*");cout<<endl;
	}
	else if(choice=='5')
		return updateCustomerMenu();
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	if(choice=='1'){
		green("*Enter DVD's Inventory Number:");white("");cin>>inventoryNumber;
		green("*UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//exeDBMS1.Execute("UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";");
		//exeDBMS1.Execute("updatedDvd <- select (userId = "+idToUpdate+") dvds;");
		cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter DVD's Title:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		green("*UPDATE dvds SET dvdTitle = "+dvdTitle+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//exeDBMS1.Execute("UPDATE dvds SET dvdTitle = \""+dvdTitle+"\" WHERE userId = "+idToUpdate+";");
		//exeDBMS1.Execute("updatedDvd <- select (userId = "+idToUpdate+") dvds;");
		cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else
		return "dvdMenu";
	system("pause");
	return "primaryMenu";
}
string listDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented";
	char choice;
	title("List DVDs");
	green("*");white("(1)");green("List DVDs by ID");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("");
		//exeDBMS1.Execute("SHOW dvds;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
		system("pause");
	}else if(choice=='5');
		return "dvdMenu";
	return "primaryMenu";
}
string searchDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented";
	char choice;
	title("Search DVDs");
	green("*");white("(1)");green("Search by ID");cout<<endl;
	green("*");white("(2)");green("Search by Title");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Go back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		green("*Enter ID to search for:");white("");cin>>dvdId;
		white("*searchById <- select (dvdId = "+dvdId+") dvds;");cout<<endl;
		//exeDBMS1.Execute("searchById <- select (dvdId = "+dvdId+") dvds;");
		//exeDBMS1.Execute("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter Title to search for:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		green("*searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds;");cout<<endl;
		//exeDBMS1.Execute("searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds");
		//exeDBMS1.Execute("SHOW searchByTitle;");
		white("");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='5')
		return "dvdMenu";
	system("pause");
	return "primaryMenu";
}
string listCustomersByDvdMenu(){
	int selection=NULL;
	string userId="userId",firstName="fName",lastName="lName",phoneNumber="phone#";
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented";
	char choice;
	title("List Customers by DVD");
	green("*");white("(1)");green("List customers by DVD");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("*Enter DVD to search for:");white("");cin>>dvdId;
		white("*rentalsByDvd <- select (dvdId = "+dvdId+") rentals;");cout<<endl;
		white("*customersByIdFromRentals <- select (customersByDvd = customers)????????????????");cout<<endl;
		//exeDBMS1.Execute("rentalsByDvd <- select (dvdId = "+dvdId+") rentals;");
		//exeDBMS1.Execute("SHOW customersByDvd;");
		//exeDBMS1.Execute("customersByIdFromRentals <- select (customersByDvd = customers);");
		//exeDBMS1.Execute("SHOW customersByIdFromRentals;");
		white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+dvdId+", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}else if(choice=='5')
		return "dvdMenu";
	system("pause");
	return "primaryMenu";
}
string searchAvailableDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented";
	char choice;
	title("Search available DVDs");
	green("*");white("(1)");green("Search by ID");cout<<endl;
	green("*");white("(2)");green("Search by Title");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Go back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		green("*Enter ID to search for:");white("");cin>>dvdId;
		white("*searchById <- select (dvdId = "+dvdId+") dvds;");cout<<endl;
		//exeDBMS1.Execute("searchById <- select (dvdId = "+dvdId+") dvds;");
		//exeDBMS1.Execute("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter Title to search for:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		white("*searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds;");cout<<endl;
		//exeDBMS1.Execute("searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds");
		//exeDBMS1.Execute("SHOW searchByTitle;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='5')
		return "rentalMenu";
	system("pause");
	return "primaryMenu";
}
string checkOutDvdMenu(){
	time_t seconds = time(NULL);
	int selection=NULL;
	char checkOutDate[21],dueDate[21],choice;
	strftime(checkOutDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	seconds=seconds+259200;
	strftime(dueDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	string inventoryNumber,dvdId,dvdTitle;
	string userId,firstName,lastName,phoneNumber;
	title("Check Out DVD");
	green("*Enter DVD ID:");white("");cin>>dvdId;
	green("*Enter Customer ID:");white("");cin>>userId;
	green("*Check out date will be:");white("");cout<<checkOutDate<<endl;
	green("*Due date will be:");white("");cout<<dueDate<<endl;
	green("*");white("1");green(" to accept above information, ");white("5");green(" to change, any key to go back:");
	cin>>choice;
	if(choice=='1'){
		white("");
		white("INSERT INTO rentals VALUES FROM ("+userId+","+dvdId+",\""+checkOutDate+"\", \"out\");");cout<<endl;
		//exeDBMS1.Execute("INSERT INTO rentals VALUES FROM ("+userId+","+dvdId+",\""+checkOutDate+"\", \"out\");");
		system("pause");
	}
	else if(choice=='5')
		return "checkOutDvd";
	else
		return "rentalMenu";
	return "primaryMenu";
}
string checkInDvdMenu(){
	time_t seconds = time(NULL);
	int selection=NULL;
	char checkInDate[21],choice;
	strftime(checkInDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	string userId,dvdId;
	title("Check In DVD");
	green("*Enter DVD ID:");white("");cin>>dvdId;
	green("*Enter Customer ID:");white("");cin>>userId;
	green("*Check in date will be:");white("");cout<<checkInDate<<endl;
	green("*1 to accept above information, 5 to change, any key to go back:");
	cin>>choice;
	if(choice=='1'){
		white("");
		cout<<"UPDATE rentals SET checkInDate = \""<<checkInDate<<"\" WHERE dvdId = "+dvdId+";"<<endl;
		//exeDBMS1.Execute("UPDATE rentals SET checkInDate = \""+checkInDate+"\" WHERE dvdId = "+dvdId+";");
		system("pause");
	}
	else if(choice=='5')
		return "checkInDvd";
	else
		return "dvdMenu";
	return "primaryMenu";
}
string listRentalsByCustomerMenu(){
	int selection=NULL;
	string userId="userId";
	string dvdId="dvdIdNotImplemented",checkOutDate="checkOutNotImplemented",checkInDate="checkInNotImplemented";
	char choice;
	title("List Rentals by Customer");
	green("*");white("(1)");green("List rentals by Customer ID");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("*Enter Customer ID to search for:");white("");cin>>userId;
		white("*rentalsByCustomer <- select (userId = "+userId+") rentals;");cout<<endl;
		//exeDBMS1.Execute("rentalsByCustomer <- select (userId = "+userId+") rentals;");
		//exeDBMS1.Execute("SHOW rentalsByCustomer;");
		white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+dvdId+", "+checkOutDate+", "+checkInDate<<endl;
		system("pause");
	}else if(choice=='5');
		return "dvdMenu";
	return "primaryMenu";
}
//User choice handler
void selectionProcessor(){
	string choice="";
	choice=primaryMenu();
	while(choice!="close application"){
		if(choice=="customerMenu")
			choice=customerMenu();
		else if(choice=="dvdMenu")
			choice=dvdMenu();
		else if(choice=="rentalMenu")
			choice=rentalMenu();
		else if(choice=="addNewCustomer")
			choice=addNewCustomerMenu();
		else if(choice=="removeCustomer")
			choice=removeCustomerMenu();
		else if(choice=="updateCustomer")
			choice=updateCustomerMenu();
		else if(choice=="listCustomer")
			choice=listCustomerMenu();
		else if(choice=="searchCustomer")
			choice=searchCustomerMenu();
		else if(choice=="addNewDvd")
			choice=addNewDvdMenu();
		else if(choice=="removeDvd")
			choice=removeDvdMenu();
		else if(choice=="updateDvd")
			choice=updateDvdMenu();
		else if(choice=="listDvd")
			choice=listDvdMenu();
		else if(choice=="searchDvd")
			choice=searchDvdMenu();
		else if(choice=="listCustomersByDvd")
			choice=listCustomersByDvdMenu();
		else if(choice=="searchAvailableDvd")
			choice=searchAvailableDvdMenu();
		else if(choice=="checkOutDvd")
			choice=checkOutDvdMenu();
		else if(choice=="checkInDvd")
			choice=checkInDvdMenu();
		else if(choice=="listRentalsByCustomer")
			choice=listRentalsByCustomerMenu();
		else{
			choice=primaryMenu();
		}
	}
	system("exit");
}
//db_application main function
int main(){
	string choice;
	selectionProcessor();
	return 0;
}
