/********************************************
 * Laramie Goode, Chris Voss, Curtis Franks	*
 * CSCE-315-Project_1						*
 * Database DBMS (WIP)						*
 ********************************************/
#include <Windows.h>//provides for SetConsoleTextAttribute() used in formatting
#include <time.h>//definitions of functions to get and manipulate date and time info.
#include "DBMS.h"//provides <iostream><string> and DBMS Class

using namespace std;

DBMS exeDBMS1(false, 0, "./");//global dbms declaration

//Formating functions: used to save space with simple repetitive format code
void white(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<print;//simply takes a string to print and ensures it is white font
}  
void green(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	cout<<print;//simply takes a string to print and ensures it is green font
}
void red(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cout<<print;//simply takes a string to print and ensures it is green font
}
void centerstring(char* s)
{
   int l=strlen(s);
   int pos=(int)((80-l)/2);
   for(int i=0;i<pos;i++)
		cout<<" ";	//adds an appropriate amount of spaces before the passed string so that it 
   cout<<s<<endl;		//centers on a normal 80 character wide console
}
void title(char* currentTitle){
	system("cls");
	for(int i=0;i<80;i++)
		green("*");
	white("");centerstring(currentTitle);
	for(int i=0;i<80;i++)
		green("*");
	cout<<endl;
}
//Root Menus: basic root menus that only accept certain numerical input
//for the next available menu options.  Each returns a menu option string
//to selectionProcessor()
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
//Database Command Menus:use simple cin and getline to accept user options
//and data input.  Each sends a strings to the dbms.Execute() based on the 
//user input and finally returns a menu option string to selectionProcessor()
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
		white("INSERT INTO customers VALUES FROM (\""+userId+"\",\""+firstName+"\",\""+lastName+"\",\""+phoneNumber+"\");");cout<<endl;//printSTok();
		exeDBMS1.Execute("OPEN customers;");
		exeDBMS1.Execute("INSERT INTO customers VALUES FROM (\""+userId+"\",\""+firstName+"\",\""+lastName+"\",\""+phoneNumber+"\");");
		exeDBMS1.Execute("SHOW customers;");
		exeDBMS1.Execute("CLOSE customers;");

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
	string userId,firstName="fNameNA",lastName="lNameNA",phoneNumber="phone#NA",idToDelete;
	char choice;
	title("Remove Customer");
	green("*Enter Customer's User ID:");white("");cin>>idToDelete;
	white("customerToDelete <- select (userId == "+idToDelete+") customers;");cout<<endl;//printSTok();
	white("SHOW customerToDelete;");cout<<endl;
	//red("");centerstring("NOT YET IMPLEMENTED");
	exeDBMS1.Execute("OPEN customers;");
	exeDBMS1.Execute("customerToDelete <- select (userId == "+idToDelete+") customers;");
	exeDBMS1.Execute("SHOW customerToDelete;");
	exeDBMS1.Execute("CLOSE customers;");
	white("");cout<<idToDelete<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	green("*");white("1");green(" to Remove the above customer, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("DELETE FROM customers WHERE (userId == "+idToDelete+");");white("");cout<<endl;
		red("");centerstring("NOT YET IMPLEMENTED");
		exeDBMS1.Execute("OPEN customers;");
		exeDBMS1.Execute("DELETE FROM customers WHERE (userId == "+idToDelete+");");
		exeDBMS1.Execute("SHOW customers;");
		exeDBMS1.Execute("CLOSE customers;");
		white("");system("pause");
	}
	else if(choice=='5')
		return "removeCustomerMenu";
	else
		return "customerMenu";
	return "primaryMenu";
}
string updateCustomerMenu(){
	int selection=NULL;
	string userId,firstName="fNameNA",lastName="lNameNA",phoneNumber="phone#NA",idToUpdate;
	char choice;
	title("Update Customer");green("*Enter Customer's User ID:");white("");cin>>idToUpdate;
	white("customerToUpdate <- select (userId == "+idToUpdate+") customers;");cout<<endl;//printSTok();
	white("SHOW customerToUpdate;");cout<<endl;//printSTok();
	exeDBMS1.Execute("OPEN customers;");
	exeDBMS1.Execute("customerToUpdate <- select (userId == "+idToUpdate+") customers;");
	exeDBMS1.Execute("SHOW customerToUpdate;");
	exeDBMS1.Execute("CLOSE customers;");
	//red("");centerstring("NOT YET IMPLEMENTED");
	white("");cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
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
		white("UPDATE customers SET firstName == "+firstName+" WHERE userId == "+idToUpdate+";");cout<<endl;
		white("updatedCustomer <- select (userId == "+idToUpdate+") customers;");cout<<endl;
		//exeDBMS1.Execute("OPEN customers;");
		//exeDBMS1.Execute("UPDATE customers SET lastName == "+firstName+" WHERE userId == "+idToUpdate+";");
		//exeDBMS1.Execute("updatedCustomer <- select (userId == "+idToUpdate+") customers;");
		//exeDBMS1.Execute("CLOSE customers;");
		red("");centerstring("NOT YET IMPLEMENTED");
		white("");cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		green("*Enter Customer's Last Name:");white("");cin>>lastName;
		white("UPDATE customers SET lastName == "+lastName+" WHERE userId == "+idToUpdate+";");cout<<endl;
		white("updatedCustomer <- select (userId == "+idToUpdate+") customers;");cout<<endl;
		//exeDBMS1.Execute("OPEN customers;");
		//exeDBMS1.Execute("UPDATE customers SET lastName == "+lastName+" WHERE userId == "+idToUpdate+";");
		//exeDBMS1.Execute("updatedCustomer <- select (userId == "+idToUpdate+") customers;");
		//exeDBMS1.Execute("CLOSE customers;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		green("*Enter Customer's Phone Number:");white("");cin>>phoneNumber;
		white("UPDATE customers SET phoneNumber == "+phoneNumber+" WHERE userId == "+idToUpdate+";");cout<<endl;
		white("updatedCustomer <- select (userId == "+idToUpdate+") customers;");cout<<endl;
		//exeDBMS1.Execute("OPEN customers;");
		//exeDBMS1.Execute("UPDATE customers SET phoneNumber == "+phoneNumber+" WHERE userId == "+idToUpdate+";");
		//exeDBMS1.Execute("updatedCustomer <- select (userId == "+idToUpdate+") customers;");
		//exeDBMS1.Execute("CLOSE customers;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
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
		white("");
		exeDBMS1.Execute("OPEN customers;");
		exeDBMS1.Execute("SHOW customers;");
		exeDBMS1.Execute("CLOSE customers;");
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
		white("searchByFirstName <- select (firstName == \""+firstName+"\") customers;");cout<<endl;
		white("SHOW searchByFirstName;");cout<<endl;
		exeDBMS1.Execute("OPEN customers;");
		exeDBMS1.Execute("searchByFirstName <- select (firstName == \""+firstName+"\") customers;");
		exeDBMS1.Execute("SHOW searchByFirstName;");
		//red("");centerstring("NOT YET IMPLEMENTED");white("");
		exeDBMS1.Execute("CLOSE customers;");
		
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		green("*Enter Last Name to search for:");white("");cin>>lastName;
		white("searchByLastName <- select (lastName = "+lastName+") customers;");cout<<endl;
		white("SHOW searchByLastName;");cout<<endl;
		exeDBMS1.Execute("OPEN customers;");
		exeDBMS1.Execute("searchByFirstName <- select (lastName == \""+lastName+"\") customers;");
		exeDBMS1.Execute("SHOW searchByLastName;");
		exeDBMS1.Execute("CLOSE customers;");
		//red("");centerstring("NOT YET IMPLEMENTED");white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		green("*Enter Phone Number to search for:");white("");cin>>phoneNumber;
		white("searchByPhoneNumber <- select (phoneNumber == "+phoneNumber+") customers;");cout<<endl;
		white("SHOW searchByPhoneNumber;");cout<<endl;
		exeDBMS1.Execute("OPEN customers;");
		exeDBMS1.Execute("searchByPhoneNumber <- select (phoneNumber == \""+phoneNumber+"\") customers;");
		exeDBMS1.Execute("SHOW searchByPhoneNumber;");
		exeDBMS1.Execute("CLOSE customers;");
		//red("");centerstring("NOT YET IMPLEMENTED");white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='5')
		return "customerMenu";
	system("pause");
	return "primaryMenu";
}
string addNewDvdMenu(){
	time_t seconds = time(NULL);
	int selection=NULL;
	string inventoryNumber,dvdId,dvdTitle;
	char id[21],choice;
	itoa(seconds,id,10);
	title("Add New DVD");
	green("*Enter DVD ID:");white("");cin>>dvdId;
	green("*Enter DVD Title:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
	inventoryNumber=id;
	green("*Inventory Number will be:");white("");cout<<inventoryNumber<<endl;
	green("*");white("1");green(" to accept above information, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("INSERT INTO dvds VALUES FROM (\""+inventoryNumber+"\",\""+dvdId+"\",\""+dvdTitle+"\");");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("INSERT INTO dvds VALUES FROM (\""+inventoryNumber+"\",\""+dvdId+"\",\""+dvdTitle+"\");");
		exeDBMS1.Execute("SHOW dvds;");
		exeDBMS1.Execute("CLOSE dvds;");
		system("pause");
	}else if(choice=='5')
		return "addNewDvdMenu";
	else
		return "dvdMenu";
	return "primaryMenu";
}
string removeDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA",idToDelete;	char choice;
	title("Remove DVD");
	green("*Enter Inventory Number to remove:");white("");cin>>idToDelete;
	white("dvdToDelete <- select (inventoryNumber == "+idToDelete+") dvds;");cout<<endl;
	white("SHOW dvdToDelete;");cout<<endl;
	exeDBMS1.Execute("OPEN dvds;");
	exeDBMS1.Execute("dvdToDelete <- select (dvdId == "+idToDelete+") dvds;");
	exeDBMS1.Execute("SHOW dvdToDelete;");
	exeDBMS1.Execute("CLOSE dvds;");
	//red("");centerstring("NOT YET IMPLEMENTED");white("");
	cout<<idToDelete<<", "+dvdId+", "+dvdTitle<<endl;
	green("*");white("1");green(" to Remove the above DVD, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("DELETE FROM dvds WHERE (inventoryNumber == "+idToDelete+");");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("DELETE FROM dvds WHERE (inventoryNumber = "+idToDelete+");");
		exeDBMS1.Execute("CLOSE dvds;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
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
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA",idToUpdate;
	char choice;
	title("Update DVD");
	green("*Enter Inventory Number:");white("");cin>>idToUpdate;
	white("dvdToUpdate <- select (inventoryNUmber == "+idToUpdate+") dvds;");cout<<endl;
	white("SHOW dvdToUpdate;");cout<<endl;
	exeDBMS1.Execute("OPEN dvds;");
	exeDBMS1.Execute("dvdToUpdate <- select (inventoryNumber == "+idToUpdate+") dvds;");
	exeDBMS1.Execute("SHOW dvdToUpdate;");
	exeDBMS1.Execute("CLOSE dvds;");
	//red("");centerstring("NOT YET IMPLEMENTED");white("");
	cout<<idToUpdate<<", "+dvdId+", "+dvdTitle<<endl;
	green("*");white("1");green(" to Update the DVD, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("*");white("(1)");green("Change DVD ID");cout<<endl;
		green("*");white("(2)");green("Change DVD Title");cout<<endl;
		green("*");cout<<endl;
	}
	else if(choice=='5')
		return updateCustomerMenu();
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	if(choice=='1'){
		green("*Enter DVD's ID:");white("");cin>>dvdId;
		white("UPDATE dvds SET dvdId == "+dvdId+" WHERE inventoryNumber == "+idToUpdate+";");cout<<endl;
		white("updatedDvd <- select (inventoryNumber == "+idToUpdate+") dvds;");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("UPDATE dvds SET dvdId == "+dvdId+" WHERE inventoryNumber == "+idToUpdate+";");
		exeDBMS1.Execute("updatedDvd <- select (inventoryNumber == "+idToUpdate+") dvds;");
		exeDBMS1.Execute("CLOSE dvds;");
		//red("");centerstring("NOT YET IMPLEMENTED");white("");
		cout<<inventoryNumber<<", "+dvdId+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter DVD's Title:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		white("UPDATE dvds SET dvdTitle == "+dvdTitle+" WHERE inventoryNumber == "+idToUpdate+";");cout<<endl;
		white("updatedDvd <- select (inventoryNumber == "+idToUpdate+") dvds;");cout<<endl;
		//exeDBMS1.Execute("OPEN dvds;");
		//exeDBMS1.Execute("UPDATE dvds SET dvdTitle == \""+dvdTitle+"\" WHERE inventoryNumber == "+idToUpdate+";");
		//exeDBMS1.Execute("updatedDvd <- select (inventoryNumber == "+idToUpdate+") dvds;");
		//exeDBMS1.Execute("CLOSE dvds;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
		cout<<inventoryNumber<<", "+dvdId+", "+dvdTitle<<endl;
	}
	else
		return "dvdMenu";
	system("pause");
	return "primaryMenu";
}
string listDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA";
	char choice;
	title("List DVDs");
	green("*");white("(1)");green("List DVDs by ID");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		white("SHOW dvds;");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("SHOW dvds;");
		exeDBMS1.Execute("CLOSE dvds;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
		system("pause");
	}else if(choice=='5');
		return "dvdMenu";
	return "primaryMenu";
}
string searchDvdMenu(){
	int selection=NULL;
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA";
	char choice;
	title("Search DVDs");
	green("*");white("(1)");green("Search by DVD ID");cout<<endl;
	green("*");white("(2)");green("Search by Title");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Go back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		green("*Enter ID to search for:");white("");cin>>dvdId;
		white("searchById <- select (dvdId == "+dvdId+") dvds;");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("searchById <- select (dvdId == "+dvdId+") dvds;");
		exeDBMS1.Execute("SHOW searchById;");
		exeDBMS1.Execute("CLOSE dvds;");
		//red("");centerstring("NOT YET IMPLEMENTED");white("");
		//for(int i=0;i<10;i++)
			//cout<<inventoryNumber<<", "+dvdId+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter Title to search for:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		white("searchByTitle <- select (dvdTitle == "+dvdTitle+") dvds;");cout<<endl;
		white("SHOW searchByTitle");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("searchByTitle <- select (dvdTitle == "+dvdTitle+") dvds");
		exeDBMS1.Execute("SHOW searchByTitle;");
		exeDBMS1.Execute("CLOSE dvds;");
		//red("");centerstring("NOT YET IMPLEMENTED");white("");
		//for(int i=0;i<10;i++)
			//cout<<inventoryNumber<<", "+dvdId+", "+dvdTitle<<endl;
	}
	else if(choice=='5')
		return "dvdMenu";
	system("pause");
	return "primaryMenu";
}
string listCustomersByDvdMenu(){
	int selection=NULL;
	string userId="userId",firstName="fName",lastName="lName",phoneNumber="phone#";
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA";
	char choice;
	title("List Customers by DVD");
	green("*");white("(1)");green("List customers by DVD");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("*Enter DVD ID to search for:");white("");cin>>dvdId;
		white("inventoryNumbersByDvdId <- select (dvdId == "+dvdId+") dvds;");cout<<endl;
		white("rentalsByInventoryNumber <- inventoryNumbersByDvdId * rentals;");cout<<endl;
		white("customersByIdFromRentals <- customers * retnalsByInventoryNUmber;");cout<<endl;
		white("customerListByDvdId <- project (dvdId, firstName, lastName, checkOutDate, checkInDate) customersByIdFromRentals;");cout<<endl;
		//exeDBMS1.Execute("OPEN dvds;");
		//exeDBMS1.Execute("inventoryNumbersByDvdId <- select (dvdId == "+dvdId+") dvds;");
		//exeDBMS1.Execute("rentalsByInventoryNumber <- inventoryNumbersByDvdId * rentals;");
		//exeDBMS1.Execute("customersByIdFromRentals <- customers * retnalsByInventoryNUmber;");
		//exeDBMS1.Execute("customerListByDvdId <- project (dvdId, firstName, lastName, checkOutDate, checkInDate) customersByIdFromRentals;");
		//exeDBMS1.Execute("CLOSE dvds;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
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
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA";
	char choice;
	title("Search available DVDs");
	green("*");white("(1)");green("Search by DVD ID");cout<<endl;
	green("*");white("(2)");green("Search by Title");cout<<endl;
	green("*");cout<<endl;
	green("*");white("(5)");green("Go back to main menu");cout<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		green("*Enter ID to search for:");white("");cin>>dvdId;
		white("searchById <- select (dvdId == "+dvdId+") dvds;");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("searchById <- select (dvdId == "+dvdId+") dvds;");
		//exeDBMS1.Execute("SHOW searchById;");
		exeDBMS1.Execute("CLOSE dvds;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter Title to search for:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		white("searchByTitle <- select (dvdTitle == "+dvdTitle+") dvds;");cout<<endl;
		exeDBMS1.Execute("OPEN dvds;");
		exeDBMS1.Execute("searchByTitle <- select (dvdTitle == "+dvdTitle+") dvds");
		//exeDBMS1.Execute("SHOW searchByTitle;");
		exeDBMS1.Execute("CLOSE dvds;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
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
	string inventoryNumber="inv#NA",dvdId="dvdIdNA",dvdTitle="dvdTitleNA";
	char checkOutDate[21],dueDate[21],choice;
	strftime(checkOutDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	seconds=seconds+259200;
	strftime(dueDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	string userId,firstName,lastName,phoneNumber;
	title("Check Out DVD");
	green("*Enter Inventory Number:");white("");cin>>inventoryNumber;
	green("*Enter Customer ID:");white("");cin>>userId;
	green("*Check out date will be:");white("");cout<<checkOutDate<<endl;
	green("*Due date will be:");white("");cout<<dueDate<<endl;
	green("*");white("1");green(" to accept above information, ");white("5");green(" to change, any key to go back:");
	cin>>choice;
	if(choice=='1'){
		white("");
		white("INSERT INTO rentals VALUES FROM (\""+userId+"\",\""+inventoryNumber+"\",\""+checkOutDate+"\", \"out\");");cout<<endl;
		exeDBMS1.Execute("OPEN rentals;");
		exeDBMS1.Execute("INSERT INTO rentals VALUES FROM (\""+userId+"\",\""+inventoryNumber+"\",\""+checkOutDate+"\", \"out\");");
		exeDBMS1.Execute("SHOW rentals;");
		exeDBMS1.Execute("CLOSE rentals;");
		system("pause");
	}
	else if(choice=='5')
		return "checkOutDvd";
	else
		return "rentalMenu";
	return "primaryMenu";
}
string checkInDvdMenu()
{
	time_t seconds = time(NULL);
	int selection=NULL;
	char checkInDate[21],choice;
	strftime(checkInDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	string userId,dvdId,inventoryNumber;
	title("Check In DVD");
	green("*Enter Inventory Number:");white("");cin>>inventoryNumber;
	green("*Enter Customer ID:");white("");cin>>userId;
	green("*Check in date will be:");white("");cout<<checkInDate<<endl;
	green("*");white("1");green(" to accept above information, ");white("5");green(" to change, any key to go back:");
	cin>>choice;
	if(choice=='1'){
		white("");
		cout<<"UPDATE rentals SET checkInDate == \""<<checkInDate<<"\" WHERE dvdId == "+dvdId+";"<<endl;
		//exeDBMS1.Execute("OPEN rentals;");
		//exeDBMS1.Execute("UPDATE rentals SET checkInDate == \""+checkInDate+"\" WHERE dvdId == \""+dvdId+"\";");
		//exeDBMS1.Execute("CLOSE rentals;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
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
	string rentalId="rentalIdNA",dvdId="dvdIdNA",checkOutDate="checkOutNA",checkInDate="checkInNA";
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
		white("rentalsByCustomer <- select (userId == "+userId+") rentals;");cout<<endl;
		white("SHOW rentalsByCustomer;");cout<<endl;
		exeDBMS1.Execute("OPEN rentals;");
		exeDBMS1.Execute("rentalsByCustomer <- select (userId == "+userId+") rentals;");
		exeDBMS1.Execute("SHOW rentalsByCustomer;");
		exeDBMS1.Execute("CLOSE rentals;");
		red("");centerstring("NOT YET IMPLEMENTED");white("");
		white("");
		for(int i=0;i<10;i++)
			cout<<rentalId<<", "+userId+", "+dvdId+", "+checkOutDate+", "+checkInDate<<endl;
		system("pause");
	}else if(choice=='5');
		return "rentalMenu";
	return "primaryMenu";
}
//Initial Database Creation: looks for the DVD Rental datbases and creates
//them if they are not available.
void createDatabases(){
	ifstream customers("./customers.db");
	ifstream dvds("./dvds.db");
	ifstream rentals("./rentals.db");
	if (!customers.good()){
		white("CREATE TABLE customers;");cout<<endl;
		exeDBMS1.Execute("CREATE TABLE customers (userId VARCHAR(20), firstName VARCHAR(20), lastName VARCHAR(20), phoneNumber VARCHAR(20)) PRIMARY KEY (userId);");
		exeDBMS1.Execute("WRITE customers;");
	}
	if (!dvds.good()){
		white("CREATE TABLE dvds;");cout<<endl;
		exeDBMS1.Execute("CREATE TABLE dvds (inventoryNumber VARCHAR(20), dvdId VARCHAR(20), title VARCHAR(20)) PRIMARY KEY (inventoryNumber);");
		exeDBMS1.Execute("WRITE dvds;");
	}
	if (!rentals.good()){
		white("CREATE TABLE rentals;");cout<<endl;
		exeDBMS1.Execute("CREATE TABLE rentals (rentalId VARCHAR(20), userId VARCHAR(20), inventoryNumber VARCHAR(20), checkOutDate VARCHAR(20), checkInDate VARCHAR(20)) PRIMARY KEY (rentalId);");
		exeDBMS1.Execute("WRITE rentals;");
	}
	system("pause");
}
//User choice handler: all of the above Command Menus are called from here
//and the strings they return, determine which next Command Menu is called.
void selectionProcessor(){
	string choice="";
	char exitChoice;
	createDatabases();
	choice=primaryMenu();
	while(choice!=""){
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
		else if(choice=="close application"){
			system("cls");
			for(int i=0;i<5;i++)
				cout<<endl;
			white("");centerstring("Are you sure you wish to exit the Database Application?");
			white("");centerstring("Enter Y to exit and N to continue");cout<<endl;
			do{
				cin>>exitChoice;
			}while(exitChoice!='y'&&exitChoice!='Y'&&exitChoice!='n'&&exitChoice!='N');
			if(exitChoice=='y'||exitChoice=='Y')
				exit(1);
		}
		else
			choice=primaryMenu();
	}
}
//db_application main function: simply calls the above selectionProcessor
int main(){
	selectionProcessor();
	return 0;
}
