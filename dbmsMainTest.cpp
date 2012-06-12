
#include <iostream>//|
#include "DBMS.h"

using namespace std;

int main1(){
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
	DBMS* dbms1 = new DBMS(true, 7);
	delete dbms1;
	cout<<"LEAVING MAIN!!!\n\n\n";	
		
	return 0;
}




int main(){
	DBMS* dbms1 = new DBMS(false, 0);
	Relation importedTable = dbms1->readFromFile("test.db");
	Relation table("foo");
	Relation table2("bar");
	Relation crossTable("cross");
	Relation unionTable("union");
	Relation diffTable("diff");
	
	DataType charType(false, 20);
	DataType intType(true);
	
	table.addAttribute("FOO", charType);
	table.addAttribute("REDDIT", charType);
	table.addAttribute("BAR", charType);
	
	table2.addAttribute("FOO", charType);
	table2.addAttribute("REDDIT", charType);
	table2.addAttribute("BAR", charType);
	vector<string> table1_input(3);
	table1_input[0] = "MINE";
	table1_input[1] = "SPLIN";
	table1_input[2] = "HALO";
	
	vector<string> table1_input2(3);
	table1_input2[0] = "DIABLO";
	table1_input2[1] = "SC2";
	table1_input2[2] = "HL1";

	vector<string> table2_input(3);
	table2_input[0] = "ZELDA";
	table2_input[1] = "PORTAL";
	table2_input[2] = "GHOST";
	
	Relation blah("hoo");
	blah.addAttribute("FOO", charType);
	blah.addAttribute("REDDIT", charType);
	blah.addAttribute("BAR", charType);
	
	/*
	blah.addTuple( table.constructTupleFromIndex(0) );
	vector<string> kop = table.constructTupleFromIndex(0);
	cout << ">>>>>>>>>>>>><<<<<<<<<<<<<\n";
	for(int i = 0; i < kop.size(); i++) {
		cout << kop[i] << '\t';
	}
	cout << ">>>>>>>>>>>>><<<<<<<<<<<<<\n";	
	wait(); */

	table.addTuple(table1_input);
	table.addTuple(table1_input2);
	
	table2.addTuple(table1_input);
	table2.addTuple(table2_input);

	crossTable.crossProduct(table, importedTable);
	unionTable.tableUnion(table, table2);
	diffTable.tableUnion(table, table2);
	

	cout << "Table:\n";
	table.print();
	cout << "----------------------------------------------\n";

	cout << "Table2:\n";
	table2.print();
	cout << "----------------------------------------------\n";

	
	cout << "Imported Table:\n";
	importedTable.print();
	cout << "----------------------------------------------\n";
	
	cout << "Cross Product of Table and Imported Table:\n";
	crossTable.print();
	cout << "----------------------------------------------\n";
	
	//wait();

	//writeToFile<Relation>(crossTable);
	
	cout << "o4ifjal;sefjaw;efljas\n";
	cout << crossTable.stringify() << '\n';
	cout << "o4ifjal;sefjaw;efljas\n";
	
	table.deleteTuple(1);
	cout << "Table after deleting index 1 (2nd row)\n";
	table.print();
	cout << "----------------------------------------------\n";
	
	cout << "Table and Table2 have same attributes?\n";
	if(unionTable.matchingAttributes(table, table2)) {
		cout << "True!\n";
	} else {
		cout << "False!\n";
	}
	cout << "----------------------------------------------\n";	
	
	cout << "Table + Table2\n";
	unionTable.print();
	cout << "----------------------------------------------\n";	
	
	//wait();
	delete dbms1;

	return 0;
}



