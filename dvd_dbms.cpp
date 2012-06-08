#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>
#include <limits>
#include <time.h>
//#include <dbparser.h>

using namespace std;
void centerstring(char* s)
{
   int l=strlen(s);
   int pos=(int)((80-l)/2);
   for(int i=0;i<pos;i++)
    cout<<" ";

   cout<<s;
}
void title(char* currentTitle){
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
	cout<<"*Enter Customer's First Name:";cin>>firstName;
	cout<<"*Enter Customer's Last Name:";cin>>lastName;
	cout<<"*Enter Customer's Phone Number:";cin>>phoneNumber;
	userId=firstName.substr(0,3)+lastName.substr(0,3)+id[4]+id[5]+id[7]+id[8]+id[9];
	cout<<"*Customer's user ID will be:"<<userId<<endl;
	cout<<"*1 to accept above information, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+","+phoneNumber+");"<<endl;
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
	cout<<"*Enter Customer's User ID:";cin>>idToDelete;
	cout<<"customerToDelete <- select (userId = "+idToDelete+") customers;"<<endl;
	//Parser("customerToDelete <- select (userId = "+idToDelete+") customers;");
	//Parser("SHOW customerToDelete;");
	cout<<idToDelete<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	cout<<"*1 to remove the above customer, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"DELETE FROM customers WHERE (userId = "+idToDelete+");"<<endl;
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
	cout<<"*Enter Customer's User ID:";cin>>idToUpdate;
	cout<<"*customerToUpdate <- select (userId = "+idToUpdate+") customers;"<<endl;
	//Parser("customerToUpdate <- select (userId = "+idToUpdate+") customers;");
	//Parser("SHOW customerToUpdate;");
	cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	cout<<"*1 to update customer, 5 to change customer to update, any key to go back:";
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
		cout<<"*Enter Customer's First Name:";cin>>firstName;
		cout<<"*UPDATE customers SET firstName = "+firstName+" WHERE userId = "+idToUpdate+";"<<endl;
		//Parser("UPDATE customers SET lastName = "+firstName+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		cout<<"*Enter Customer's Last Name:";cin>>lastName;
		cout<<"*UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";"<<endl;
		//Parser("UPDATE customers SET lastName = "+lastName+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedCustomer <- select (userId = "+idToUpdate+") customers;");
		cout<<idToUpdate<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		cout<<"*Enter Customer's Phone Number:";cin>>phoneNumber;
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
	cout<<"*(1)List customers by User ID"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		//Parser("SHOW customers;");
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
	cout<<"*(1)Search by First Name"<<endl;
	cout<<"*(2)Search by Last Name"<<endl;
	cout<<"*(3)Search by Phone NUmber"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Go back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='3');
	if(choice=='1'){
		cout<<"*Enter First Name to search for:";cin>>firstName;
		cout<<"*searchByFirstName <- select (firstName = "+firstName+") customers;"<<endl;
		//Parser("searchByFirstName <- select (firstName = "+firstName+") customers;");
		//Parser("SHOW searchByFirstName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='2'){
		cout<<"*Enter Last Name to search for:";cin>>lastName;
		cout<<"*searchByFirstName <- select (lastName = "+lastName+") customers;"<<endl;
		//Parser("searchByFirstName <- select (lastName = "+lastName+") customers;");
		//Parser("SHOW searchByLastName;");
		for(int i=0;i<10;i++)
			cout<<userId<<", "+firstName+", "+lastName+", "+phoneNumber<<endl;
	}
	else if(choice=='3'){
		cout<<"*Enter Phone Number to search for:";cin>>phoneNumber;
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
	time_t seconds = time(NULL);
	int selection=NULL;
	string inventoryNumber,dvdId,dvdTitle;
	char id[21],choice;
	itoa(seconds,id,10);
	title("Add New DVD");
	cout<<"*Enter DVD ID:";cin>>dvdId;
	cout<<"*Enter DVD Title:";
	inventoryNumber=id;
	cout<<"*Inventory Number will be:"<<inventoryNumber<<endl;
	cout<<"*1 to accept above information, 5 to change, any key to go back:";
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"INSERT INTO dvds VALUES FROM ("+inventoryNumber+","+dvdId+",\""+dvdTitle+"\");"<<endl;
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
	cout<<"*Enter DVD ID to remove:";cin>>idToDelete;
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
	cout<<"*Enter DVD ID:";cin>>idToUpdate;
	cout<<"*dvdToUpdate <- select (userId = "+idToUpdate+") dvds;"<<endl;
	//Parser("dvdToUpdate <- select (dvdId = "+idToUpdate+") dvds;");
	//Parser("SHOW dvdToUpdate;");
	cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	cout<<"*1 to update DVD, 5 to change DVD to update, any key to go back:";
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
		cout<<"*Enter DVD's Inventory Number:";cin>>inventoryNumber;
		cout<<"*UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";"<<endl;
		//Parser("UPDATE dvds SET inventoryNumber = "+inventoryNumber+" WHERE userId = "+idToUpdate+";");
		//Parser("updatedDvd <- select (userId = "+idToUpdate+") dvds;");
		cout<<idToUpdate<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		cout<<"*Enter DVD's Title:";cin.clear();cin.sync();getline(cin,dvdTitle);
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
	cout<<"*(1)List DVDs by ID"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
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
	cout<<"*(1)Search by ID"<<endl;
	cout<<"*(2)Search by Title"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Go back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		cout<<"*Enter ID to search for:";cin>>dvdId;
		cout<<"*searchById <- select (dvdId = "+dvdId+") dvds;"<<endl;
		//Parser("searchById <- select (dvdId = "+dvdId+") dvds;");
		//Parser("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		cout<<"*Enter Title to search for:";cin.clear();cin.sync();getline(cin,dvdTitle);
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
	cout<<"*(1)List customers by DVD"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='5');
	if(choice=='1'){
		cout<<"*Enter DVD to search for:";cin>>dvdId;
		cout<<"*rentalsByDvd <- select (dvdId = "+dvdId+") rentals;"<<endl;
		cout<<"*customersByIdFromRentals <- select (customersByDvd = customers)????????????????"<<endl;
		//Parser("rentalsByDvd <- select (dvdId = "+dvdId+") rentals;");
		//Parser("SHOW customersByDvd;");
		//Parser("customersByIdFromRentals <- select (customersByDvd = customers);??????????????????????????
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
	cout<<"*(1)Search by ID"<<endl;
	cout<<"*(2)Search by Title"<<endl;
	cout<<"*"<<endl;
	cout<<"*(5)Go back to main menu"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2'&&choice!='5');
	if(choice=='1'){
		cout<<"*Enter ID to search for:";cin>>dvdId;
		cout<<"*searchById <- select (dvdId = "+dvdId+") dvds;"<<endl;
		//Parser("searchById <- select (dvdId = "+dvdId+") dvds;");
		//Parser("SHOW searchById;");
		for(int i=0;i<10;i++)
			cout<<dvdId<<", "+inventoryNumber+", "+dvdTitle<<endl;
	}
	else if(choice=='2'){
		cout<<"*Enter Title to search for:";cin.clear();cin.sync();getline(cin,dvdTitle);
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
	return NULL;
}
string checkInDvdMenu(){
	return NULL;
}
string listRentalsByCustomerMenu(){
	return NULL;
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
			choice=primaryMenu("not yet implemented");
		else if(choice=="checkInDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="listRentalsByCustomer")
			choice=primaryMenu("not yet implemented");
		else{
			choice=primaryMenu("DVD Database Management System");
		}
	}
	system("exit");
}
int main(){
	string choice;
	selectionProcessor();
	cout<<"* Press ENTER to quit";
	getline(cin, choice);
	return 0;
}
