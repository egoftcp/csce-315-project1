#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>
#include <limits>
#include <time.h>
#include <dbparser.h>

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
	else if(selection==0)return "exit";
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
	else if(selection==0)return "exit";
	else return "primaryMenu";
}
string addNewCustomerMenu(){
	time_t seconds = time(NULL);
	int selection=NULL,idNum=seconds;
	string userId,firstName,lastName,phoneNumber;
	char id[21],choice;
	title("Add New Customer");
	cout<<"*Enter Customer's First Name:";cin>>firstName;
	cout<<"*Enter Customer's Last Name:";cin>>lastName;
	cout<<"*Enter Customer's Phone Number:";cin>>phoneNumber;
	userId=firstName+lastName+itoa(seconds,id,10);
	cout<<"*Customer's user ID will be:"<<userId<<endl;
	cout<<"*1 to accept above information, 5 to change, any key to go back:";
//	do{
		cin>>choice;
//	}while(choice!='1'||choice!='5');
	if(choice=='1')
		Parser("INSERT INTO customers VALUES FROM ("+userId+","+firstName+","+lastName+","+phoneNumber+");");
	else if(choice=='1')
		addNewCustomerMenu();
	else
		return "customerMenu";
}
string removeCustomerMenu(){
	return NULL;
}
string updateCustomerMenu(){
	return NULL;
}
string listCustomerMenu(){
	return NULL;
}
string searchCustomerMenu(){
	return NULL;
}
string addNewDvdMenu(){
	return NULL;
}
string removeNewDvdMenu(){
	return NULL;
}
string updateDvdMenu(){
	return NULL;
}
string listDvdMenu(){
	return NULL;
}
string searchDvdMenu(){
	return NULL;
}
string listCustomerByDvdMenu(){
	return NULL;
}
string searchAvailableDvdMenu(){
	return NULL;
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
			choice=primaryMenu("not yet implemented");
		else if(choice=="updateCustomer")
			choice=primaryMenu("not yet implemented");
		else if(choice=="listCustomer")
			choice=primaryMenu("not yet implemented");
		else if(choice=="searchCustomer")
			choice=primaryMenu("not yet implemented");
		else if(choice=="addNewDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="removeDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="updateDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="listDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="searchDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="listCustomersByDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="searchAvailableDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="checkOutDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="checkInDvd")
			choice=primaryMenu("not yet implemented");
		else if(choice=="listRentalsByCustomer")
			choice=primaryMenu("not yet implemented");
		else{
			choice="";
			primaryMenu("DVD Database Management System");
		}
	}
}

int main(){
	string choice;
	selectionProcessor();
	cout<<"* Press ENTER to quit";
	getline(cin, choice);
	return 0;
}