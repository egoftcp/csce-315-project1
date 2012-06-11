#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>
#include <limits>
#include <time.h>
//#include <Parser.h>
//#include <DatabaseEngine.h>

using namespace std;
bool exec;
void white(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<<print;
}
void green(string print){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	cout<<print;
}
void centerstring(char* s)
{
   int l=strlen(s);
   int pos=(int)((80-l)/2);
   for(int i=0;i<pos;i++)
    white(" ");
   cout<<s;
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


string primaryMenu(char* primaryTitle){
	int selection=NULL;
	cin.clear();
	title(primaryTitle);
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
		white("INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+","+phoneNumber+");");cout<<endl;
		//Parser("INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+","+phoneNumber+");");
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
	green("customerToDelete <- select (userId = "+idToDelete+") customers;");cout<<endl;
	//Parser("customerToDelete <- select (userId = "+idToDelete+") customers;");
	//Parser("SHOW customerToDelete;");
	cout<<idToDelete<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	green("*");white("1");green(" to Remove the above customer, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		white("DELETE FROM customers WHERE (userId = "+idToDelete+");");cout<<endl;
		//Parser("DELETE FROM customers WHERE (userId = "+idToDelete+");");
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
	white("*customerToUpdate <- select (userId = "+idToUpdate+") customers;");cout<<endl;
	//Parser("customerToUpdate <- select (userId = "+idToUpdate+") customers;");
	//Parser("SHOW customerToUpdate;");
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
		white("*UPDATE customers SET firstName = "+firstName+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//Parser("UPDATE customers SET lastName = "+firstName+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		green("*Enter Customer's Last Name:");white("");cin>>lastName;
		white("*UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//Parser("UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		green("*Enter Customer's Phone Number:");white("");cin>>phoneNumber;
		white("*UPDATE customers SET phoneNumber = "+phoneNumber+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//Parser("UPDATE customers SET phoneNumber = "+phoneNumber+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
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
		//Parser("SHOW customers;");
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
		//Parser("searchByFirstName <- select (firstName = "+firstName+") customers;");
		//Parser("SHOW searchByFirstName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		green("*Enter Last Name to search for:");white("");cin>>lastName;
		green("*searchByFirstName <- select (lastName = "+lastName+") customers;");cout<<endl;
		//Parser("searchByFirstName <- select (lastName = "+lastName+") customers;");
		//Parser("SHOW searchByLastName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		green("*Enter Phone Number to search for:");white("");cin>>phoneNumber;
		green("*searchByFirstName <- select (phoneNumber = "+phoneNumber+") customers;");cout<<endl;
		//Parser("searchByPhoneNumber <- select (phoneNumber = "+phoneNumber+") customers;");
		//Parser("SHOW searchByPhoneNumber;");
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
		//Parser("INSERT INTO dvds VALUES FROM ("+inventoryNumber+","+dvdId+",\""+title+"\");");
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
	//Parser("dvdToDelete <- select (dvdId = "+idToDelete+") dvds;");
	//Parser("SHOW dvdToDelete;");
	cout<<idToDelete<<", "+inventoryNumber+", "+dvdTitle<<endl;
	green("*");white("1");green(" to Remove the above DVD, ");white("5");green(" to change, any key to go back:");
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		green("DELETE FROM dvds WHERE (dvdId = "+idToDelete+");");cout<<endl;
		//Parser("DELETE FROM dvds WHERE (dvdId = "+idToDelete+");");
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
	//Parser("dvdToUpdate <- select (dvdId = "+idToUpdate+") dvds;");
	//Parser("SHOW dvdToUpdate;");
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
		//Parser("UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedDvd <- select (userId = "+idToUpdate+") dvds;");
		cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter DVD's Title:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		green("*UPDATE dvds SET dvdTitle = "+dvdTitle+" WHERE userId = "+idToUpdate+";");cout<<endl;
		//Parser("UPDATE dvds SET dvdTitle = \""+dvdTitle+"\" WHERE userId = "+idToUpdate+";");
		//Parser("updatedDvd <- select (userId = "+idToUpdate+") dvds;");
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
		//Parser("SHOW dvds;");
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
		//Parser("searchById <- select (dvdId = "+dvdId+") dvds;");
		//Parser("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter Title to search for:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		green("*searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds;");cout<<endl;
		//Parser("searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds");
		//Parser("SHOW searchByTitle;");
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
		//Parser("rentalsByDvd <- select (dvdId = "+dvdId+") rentals;");
		//Parser("SHOW customersByDvd;");
		//Parser("customersByIdFromRentals <- select (customersByDvd = customers);");
		//Parser("SHOW customersByIdFromRentals;");
		white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+dvdId+", "+firstName+", "+lastName+", "+phoneNumber<<endl;
		system("pause");
	}else if(choice=='5');
		return "dvdMenu";
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
		//Parser("searchById <- select (dvdId = "+dvdId+") dvds;");
		//Parser("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		green("*Enter Title to search for:");white("");cin.clear();cin.sync();getline(cin,dvdTitle);
		white("*searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds;");cout<<endl;
		//Parser("searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds");
		//Parser("SHOW searchByTitle;");
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
		//Parser("INSERT INTO rentals VALUES FROM ("+userId+","+dvdId+",\""+checkOutDate+"\", \"out\");");
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
		//Parser("UPDATE rentals SET checkInDate = \""+checkInDate+"\" WHERE dvdId = "+dvdId+";");
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
		//Parser("rentalsByCustomer <- select (userId = "+userId+") rentals;");
		//Parser("SHOW rentalsByCustomer;");
		white("");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+dvdId+", "+checkOutDate+", "+checkInDate<<endl;
		system("pause");
	}else if(choice=='5');
		return "dvdMenu";
	return "primaryMenu";
}
void selectionProcessor(){
	string choice="";
	choice=primaryMenu("DVD Database Management System");
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
			choice=primaryMenu("DVD Database Management System");
		}
	}
	system("exit");
}
int main(){
	string choice;
	selectionProcessor();
	return 0;
}
