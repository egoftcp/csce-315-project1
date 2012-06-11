
#include <iostream>//|
#include "DBMS.h"

using namespace std;

int main(){
/* DVD_APP USAGE EXAMPLE (NOT TESTED) (SUBJECT TO CHANGE)
	string sampleCommand1 = "CREATE TABLE baseball_players (fname VARCHAR(20), lname VARCHAR(30), team VARCHAR(20), homeruns INTEGER, salary INTEGER) PRIMARY KEY (fname, lname);";
	string sampleCommand2 = "INSERT INTO baseball_players VALUES FROM (\"Joe\", \"Swatter\", \"Pirates\", 40, 1000000);";
	string sampleCommand3 = "INSERT INTO baseball_players VALUES FROM (\"Sarah\", \"Batter\", \"Dinosaurs\", 100, 5000000);";
	string sampleCommand4 = "INSERT INTO baseball_players VALUES FROM (\"Snoopy\", \"Slinger\", \"Pirates\", 3, 200000);";
	string sampleQuery1 = "high_hitters <- select (homeruns >= 40) baseball_players;"
	string sampleCommand5 = "SHOW high_hitters";
	
	DBMS exDBMS1(false, 0, "./DVDDataBase"); //use this constructor for DVD_APP
	exeDBMS1.Execute(SampleCommand1);
	string Program = sampleCommand2 + sampleCommand3 + sampleCommand4;
	exeDBMS1.Excute(Program);
	exeDBMS1.Excute(sampleQuery1);
	exeDBMS1.Excute(sampleCommand5);
*/
	cout<<"ENTERING MAIN!!!\n\n\n";
	DBMS* dbms1 = new DBMS(true);
	delete dbms1;
	cout<<"LEAVING MAIN!!!\n\n\n";	
		
	return 0;
}

