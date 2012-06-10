#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>
#include <limits>
#include <time.h>
//#include <>
//#include <DatabaseEngine.h>

using namespace std;
bool exec;
void whiteIn(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void greenOut(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
}
void centerstring(char* s)
{
   int l=strlen(s);
   int pos=(int)((80-l)/2);
   for(int i=0;i<pos;i++)
    cout<<" ";

   cout<<s;
}
void title(char* currentTitle){
	whiteIn();
	system("cls");
	for(int i=0;i<80;i++)
		cout<<"*";
	centerstring(currentTitle);
	cout<<endl;
	for(int i=0;i<80;i++)
		cout<<"*";
}


string primaryMenu(char* primaryTitle){
	int selection=NULL;
	cin.clear();
	title(primaryTitle);
	greenOut();
	cout<<"*(1)Customers"<<endl;
	cout<<"*\tAdd new customer"<<endl;
	cout<<"*\tRemove customer"<<endl;
	cout<<"*\tUpdate customer"<<endl;
	cout<<"*\tList customer"<<endl;
	cout<<"*\tSearch customer"<<endl;
	cout<<"*(2)DVDs"<<endl;
	cout<<"*\tAdd new DVD"<<endl;
	cout<<"*\tRemove DVD"<<endl;
	cout<<"*\tUpdate DVD"<<endl;
	cout<<"*\tList DVD"<<endl;
	cout<<"*\tSearch DVD"<<endl;
	cout<<"*\tList customers by DVD"<<endl;
	cout<<"*(3)Rentals"<<endl;
	cout<<"*\tSearch available DVDs"<<endl;
	cout<<"*\tCheck out DVD"<<endl;
	cout<<"*\tCheck in DVD"<<endl;
	cout<<"*\tList rentals by customer"<<endl;
	cout<<"*Options 1, 2, or 3:";cin>>selection;
	if(selection==1)return "customerMenu";
	else if(selection==2)return "dvdMenu";
	else if(selection==3)return "rentalMenu";
	else if(selection==0)return "close application";
	else return "primaryMenu";
}
string customerMenu(){
	int selection=NULL;
	title("Customer Menu");
	greenOut();
	cout<<"*   Customers"<<endl;
	cout<<"*\t(1)Add new customer"<<endl;
	cout<<"*\t(2)Remove customer"<<endl;
	cout<<"*\t(3)Update customer"<<endl;
	cout<<"*\t(4)List customer"<<endl;
	cout<<"*\t(5)Search customer"<<endl;
	cout<<"*(6)DVDs"<<endl;
	cout<<"*\tAdd new DVD"<<endl;
	cout<<"*\tRemove DVD"<<endl;
	cout<<"*\tUpdate DVD"<<endl;
	cout<<"*\tList DVD"<<endl;
	cout<<"*\tSearch DVD"<<endl;
	cout<<"*\tList customers by DVD"<<endl;
	cout<<"*(7)Rentals"<<endl;
	cout<<"*\tSearch available DVDs"<<endl;
	cout<<"*\tCheck out DVD"<<endl;
	cout<<"*\tCheck in DVD"<<endl;
	cout<<"*\tList rentals by customer"<<endl;
	cout<<"*Options 1-7:";cin>>selection;
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
	greenOut();
	cout<<"*(1)Customers"<<endl;
	cout<<"*\tAdd new customer"<<endl;
	cout<<"*\tRemove customer"<<endl;
	cout<<"*\tUpdate customer"<<endl;
	cout<<"*\tList customer"<<endl;
	cout<<"*\tSearch customer"<<endl;
	cout<<"*   DVDs"<<endl;
	cout<<"*\t(2)Add new DVD"<<endl;
	cout<<"*\t(3)Remove DVD"<<endl;
	cout<<"*\t(4)Update DVD"<<endl;
	cout<<"*\t(5)List DVD"<<endl;
	cout<<"*\t(6)Search DVD"<<endl;
	cout<<"*\t(7)List customers by DVD"<<endl;
	cout<<"*(8)Rentals"<<endl;
	cout<<"*\tSearch available DVDs"<<endl;
	cout<<"*\tCheck out DVD"<<endl;
	cout<<"*\tCheck in DVD"<<endl;
	cout<<"*\tList rentals by customer"<<endl;
	cout<<"*Options 1-9:";cin>>selection;
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
	greenOut();
	cout<<"*(1)Customers"<<endl;
	cout<<"*\tAdd new customer"<<endl;
	cout<<"*\tRemove customer"<<endl;
	cout<<"*\tUpdate customer"<<endl;
	cout<<"*\tList customer"<<endl;
	cout<<"*\tSearch customer"<<endl;
	cout<<"*(2)DVDs"<<endl;
	cout<<"*\tAdd new DVD"<<endl;
	cout<<"*\tRemove DVD"<<endl;
	cout<<"*\tUpdate DVD"<<endl;
	cout<<"*\tList DVD"<<endl;
	cout<<"*\tSearch DVD"<<endl;
	cout<<"*\tList customers by DVD"<<endl;
	cout<<"* Rentals"<<endl;
	cout<<"*\t(3)Search available DVDs"<<endl;
	cout<<"*\t(4)Check out DVD"<<endl;
	cout<<"*\t(5)Check in DVD"<<endl;
	cout<<"*\t(6)List rentals by customer"<<endl;
	cout<<"*Options 1-7:";cin>>selection;
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
	greenOut();cout<<"*Enter Customer's First Name:";whiteIn();cin>>firstName;
	greenOut();cout<<"*Enter Customer's Last Name:";whiteIn();cin>>lastName;
	greenOut();cout<<"*Enter Customer's Phone Number:";whiteIn();cin>>phoneNumber;
	userId=firstName.substr(0,3)+lastName.substr(0,3)+id[4]+id[5]+id[7]+id[8]+id[9];
	greenOut();cout<<"*Customer's user ID will be:";whiteIn();cout<<userId<<endl;
	greenOut();cout<<"*1 to accept above information, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		whiteIn();cout<<"INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+","+phoneNumber+");"<<endl;
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
	greenOut();cout<<"*Enter Customer's User ID:";whiteIn();cin>>idToDelete;
	cout<<"customerToDelete <- select (userId = "+idToDelete+") customers;"<<endl;
	//Parser("customerToDelete <- select (userId = "+idToDelete+") customers;");
	//Parser("SHOW customerToDelete;");
	cout<<idToDelete<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	greenOut();cout<<"*1 to remove the above customer, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		whiteIn();cout<<"DELETE FROM customers WHERE (userId = "+idToDelete+");"<<endl;
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
	title("Update Customer");
	greenOut();cout<<"*Enter Customer's User ID:";whiteIn();cin>>idToUpdate;
	cout<<"*customerToUpdate <- select (userId = "+idToUpdate+") customers;"<<endl;
	//Parser("customerToUpdate <- select (userId = "+idToUpdate+") customers;");
	//Parser("SHOW customerToUpdate;");
	cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	greenOut();cout<<"*1 to update customer, 5 to change customer to update, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"*(1)Change First Name"<<endl;
		cout<<"*(2)Change Last Name"<<endl;
		cout<<"*(3)Change Phone NUmber"<<endl;
	}
	else if(choice=='5')
		return updateCustomerMenu();
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='3');
	if(choice=='1'){
		greenOut();cout<<"*Enter Customer's First Name:";whiteIn();cin>>firstName;
		cout<<"*UPDATE customers SET firstName = "+firstName+" WHERE userId = "+idToUpdate+";"<<endl;
		//Parser("UPDATE customers SET lastName = "+firstName+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		greenOut();cout<<"*Enter Customer's Last Name:";whiteIn();cin>>lastName;
		cout<<"*UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";"<<endl;
		//Parser("UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		greenOut();cout<<"*Enter Customer's Phone Number:";whiteIn();cin>>phoneNumber;
		cout<<"*UPDATE customers SET phoneNumber = "+phoneNumber+" WHERE userId = "+idToUpdate+";"<<endl;
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
	greenOut();
	cout<<"*(1)List customers by User ID"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		//Parser("SHOW customers;");
		whiteIn();
		for(int i=0;i<10;i++)
			cout<<"*"<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
		system("pause");
	}else if(choice=='5');
		return "customerMenu";
	return "primaryMenu";
}
string searchCustomerMenu(){
	int selection=NULL;
	string userId="userId",firstName="fName",lastName="lName",phoneNumber="phone#";	char choice;
	title("Search Customers");
	greenOut();
	cout<<"*(1)Search by First Name"<<endl;
	cout<<"*(2)Search by Last Name"<<endl;
	cout<<"*(3)Search by Phone NUmber"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Go back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='3');
	if(choice=='1'){
		greenOut();cout<<"*Enter First Name to search for:";whiteIn();cin>>firstName;
		cout<<"*searchByFirstName <- select (firstName = "+firstName+") customers;"<<endl;
		//Parser("searchByFirstName <- select (firstName = "+firstName+") customers;");
		//Parser("SHOW searchByFirstName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		greenOut();cout<<"*Enter Last Name to search for:";whiteIn();cin>>lastName;
		cout<<"*searchByFirstName <- select (lastName = "+lastName+") customers;"<<endl;
		//Parser("searchByFirstName <- select (lastName = "+lastName+") customers;");
		//Parser("SHOW searchByLastName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		greenOut();cout<<"*Enter Phone Number to search for:";whiteIn();cin>>phoneNumber;
		cout<<"*searchByFirstName <- select (phoneNumber = "+phoneNumber+") customers;"<<endl;
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
	greenOut();cout<<"*Enter DVD ID:";whiteIn();cin>>dvdId;
	greenOut();cout<<"*Enter DVD Title:";whiteIn();cin.clear();cin.sync();getline(cin,dvdTitle);
	greenOut();cout<<"*Enter Inventory Number:";whiteIn();cin>>inventoryNumber;
	greenOut();cout<<"*1 to accept above information, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		whiteIn();cout<<"INSERT INTO dvds VALUES FROM ("+inventoryNumber+","+dvdId+",\""+dvdTitle+"\");"<<endl;
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
	greenOut();cout<<"*Enter DVD ID to remove:";whiteIn();cin>>idToDelete;
	cout<<"dvdToDelete <- select (dvdId = "+idToDelete+") dvds;"<<endl;
	//Parser("dvdToDelete <- select (dvdId = "+idToDelete+") dvds;");
	//Parser("SHOW dvdToDelete;");
	cout<<idToDelete<<", "+inventoryNumber+", "+dvdTitle<<endl;
	cout<<"*1 to remove the above DVD, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"DELETE FROM dvds WHERE (dvdId = "+idToDelete+");"<<endl;
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
	greenOut();cout<<"*Enter DVD ID:";whiteIn();cin>>idToUpdate;
	cout<<"*dvdToUpdate <- select (userId = "+idToUpdate+") dvds;"<<endl;
	//Parser("dvdToUpdate <- select (dvdId = "+idToUpdate+") dvds;");
	//Parser("SHOW dvdToUpdate;");
	cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	greenOut();cout<<"*1 to update DVD, 5 to change DVD to update, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"*(1)Change Inventory Number"<<endl;
		cout<<"*(2)Change DVD Title"<<endl;
		cout<<"*"<<endl;
	}
	else if(choice=='5')
		return updateCustomerMenu();
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	if(choice=='1'){
		greenOut();cout<<"*Enter DVD's Inventory Number:";whiteIn();cin>>inventoryNumber;
		cout<<"*UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";"<<endl;
		//Parser("UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedDvd <- select (userId = "+idToUpdate+") dvds;");
		cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		greenOut();cout<<"*Enter DVD's Title:";whiteIn();cin.clear();cin.sync();getline(cin,dvdTitle);
		cout<<"*UPDATE dvds SET dvdTitle = "+dvdTitle+" WHERE userId = "+idToUpdate+";"<<endl;
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
	greenOut();cout<<"*(1)List DVDs by ID"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		whiteIn();
		//Parser("SHOW dvds;");
		for(int i=0;i<10;i++)
			cout<<"*"<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
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
	greenOut();cout<<"*(1)Search by ID"<<endl;
	cout<<"*(2)Search by Title"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Go back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		greenOut();cout<<"*Enter ID to search for:";whiteIn();cin>>dvdId;
		cout<<"*searchById <- select (dvdId = "+dvdId+") dvds;"<<endl;
		//Parser("searchById <- select (dvdId = "+dvdId+") dvds;");
		//Parser("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		greenOut();cout<<"*Enter Title to search for:";whiteIn();cin.clear();cin.sync();getline(cin,dvdTitle);
		cout<<"*searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds;"<<endl;
		//Parser("searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds");
		//Parser("SHOW searchByTitle;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='5')
		return "customerMenu";
	system("pause");
	return "primaryMenu";
}
string listCustomersByDvdMenu(){
	int selection=NULL;
	string userId="userId",firstName="fName",lastName="lName",phoneNumber="phone#";
	string inventoryNumber="inv#NotImplemented",dvdId="dvdIdNotImplemented",dvdTitle="dvdTitleNotImplemented";
	char choice;
	title("List Customers by DVD");
	greenOut();cout<<"*(1)List customers by DVD"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		greenOut();cout<<"*Enter DVD to search for:";whiteIn();cin>>dvdId;
		cout<<"*rentalsByDvd <- select (dvdId = "+dvdId+") rentals;"<<endl;
		cout<<"*customersByIdFromRentals <- select (customersByDvd = customers)????????????????"<<endl;
		//Parser("rentalsByDvd <- select (dvdId = "+dvdId+") rentals;");
		//Parser("SHOW customersByDvd;");
		//Parser("customersByIdFromRentals <- select (customersByDvd = customers);");
		//Parser("SHOW customersByIdFromRentals;");
		for(int i=0;i<10;i++)
			cout<<"*"<<userId<<", "+dvdId+", "+firstName+", "+lastName+", "+phoneNumber<<endl;
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
	greenOut();cout<<"*(1)Search by ID"<<endl;
	cout<<"*(2)Search by Title"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Go back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		greenOut();cout<<"*Enter ID to search for:";whiteIn();cin>>dvdId;
		cout<<"*searchById <- select (dvdId = "+dvdId+") dvds;"<<endl;
		//Parser("searchById <- select (dvdId = "+dvdId+") dvds;");
		//Parser("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		greenOut();cout<<"*Enter Title to search for:";whiteIn();cin.clear();cin.sync();getline(cin,dvdTitle);
		cout<<"*searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds;"<<endl;
		//Parser("searchByTitle <- select (dvdTitle = "+dvdTitle+") dvds");
		//Parser("SHOW searchByTitle;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='5')
		return "customerMenu";
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
	greenOut();cout<<"*Enter DVD ID:";whiteIn();cin>>dvdId;
	greenOut();cout<<"*Enter Customer ID:";whiteIn();cin>>userId;
	greenOut();cout<<"*Check out date will be:";whiteIn();cout<<checkOutDate<<endl;
	greenOut();cout<<"*Due date will be:";whiteIn();cout<<dueDate<<endl;
	greenOut();cout<<"*1 to accept above information, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		whiteIn();
		cout<<"INSERT INTO rentals VALUES FROM ("+userId+","+dvdId+",\""+checkOutDate+"\", \"out\");"<<endl;
		//Parser("INSERT INTO rentals VALUES FROM ("+userId+","+dvdId+",\""+checkOutDate+"\", \"out\");");
		system("pause");
	}
	else if(choice=='5')
		return "checkOutDvdMenu";
	else
		return "dvdMenu";
	return "primaryMenu";
}
string checkInDvdMenu(){
	time_t seconds = time(NULL);
	int selection=NULL;
	char checkInDate[21],choice;
	strftime(checkInDate,20,"%Y-%m-%d %H:%M:%S",localtime(&seconds));
	string userId,dvdId;
	title("Check In DVD");
	greenOut();cout<<"*Enter DVD ID:";whiteIn();cin>>dvdId;
	greenOut();cout<<"*Enter Customer ID:";whiteIn();cin>>userId;
	greenOut();cout<<"*Check in date will be:";whiteIn();cout<<checkInDate<<endl;
	greenOut();cout<<"*1 to accept above information, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		whiteIn();
		cout<<"UPDATE rentals SET checkInDate = \""<<checkInDate<<"\" WHERE dvdId = "+dvdId+";"<<endl;
		//Parser("UPDATE rentals SET checkInDate = \""+checkInDate+"\" WHERE dvdId = "+dvdId+";");
		system("pause");
	}
	else if(choice=='5')
		return "checkOutDvdMenu";
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
	greenOut();cout<<"*(1)List rentals by Customer ID"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		greenOut();cout<<"*Enter Customer ID to search for:";whiteIn();cin>>userId;
		cout<<"*rentalsByCustomer <- select (userId = "+userId+") rentals;"<<endl;
		//Parser("rentalsByCustomer <- select (userId = "+userId+") rentals;");
		//Parser("SHOW rentalsByCustomer;");
		for(int i=0;i<10;i++)
			cout<<"*"<<userId<<", "+dvdId+", "+checkOutDate+", "+checkInDate<<endl;
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
