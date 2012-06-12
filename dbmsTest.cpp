#include <iostream>
#include "DBMS.h"

using namespace std;

int main(){
	vector<string> cmds;
	cmds.push_back("CREATE TABLE friends (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);");
	cmds.push_back("INSERT INTO friends VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);");
	cmds.push_back("INSERT INTO friends VALUES FROM (\"Smith\", \"Smith\", \"Annoying\", 5);");
	cmds.push_back("INSERT INTO friends VALUES FROM (\"Algebra\", \"Homework\", \"Boring\", -100);");
	cmds.push_back("SHOW friends;");
	cmds.push_back("WRITE friends;");
	cmds.push_back("CREATE TABLE enemies (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);");
	cmds.push_back("INSERT INTO enemies VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);");
	cmds.push_back("INSERT INTO enemies VALUES FROM (\"The\", \"Penguin\", \"Weird\", 100);");
	cmds.push_back("INSERT INTO enemies VALUES FROM (\"Joker\", \"N/A\", \"Weird\", 150);");
	cmds.push_back("SHOW enemies;");
	cmds.push_back("project_test <- project (fname, lname) friends;");
	cmds.push_back("SHOW project_test;");
	cmds.push_back("rename_test <- rename (v_fname, v_lname, v_personality, v_bounty) enemies;");
	cmds.push_back("SHOW rename_test;");
	cmds.push_back("CLOSE enemies;");
	cmds.push_back("CLOSE project_test;");
	cmds.push_back("CLOSE rename_test;");
	cmds.push_back("EXIT;");

	cout<<"This is a test of the DBMS:\n";
	DBMS* dbms = new DBMS(false,1);
	for(int i=0; i<cmds.size(); i++){
		cout<<"*** EXECUTING CMD:\n"<<cmds[i]<<endl;
		
		string line = cmds[i];
		
		int valid = dbms->Parser->Validate(line);
		if(valid == 0){
			cout<<"INVALID COMMAND or QUERY!\n";
		}else if(valid==1){
			if(!(dbms->Parser->ExecuteCommand(line))){ 
				cerr<<"Unexpected error Executing Command: "<<line<<endl;
			}
		}else if(valid==2){
			Relation* newRel = dbms->Parser->ExecuteQuery(line);
		}		
		cout<<"*** CMD COMPLETE.. Press ENTER to continue";
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		cout<<endl<<endl<<endl;
	}
	cout<<"\n\nEnd of DBMS Demo/Test.. Press ENTER to exit";
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	delete dbms;
	return 0;
	
}




int main1(){
	//THIS IS A TEST OF THE RELATION OBJECT:
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
	


	table.addTuple(table1_input);
	table.addTuple(table1_input2);
	
	table2.addTuple(table1_input);
	table2.addTuple(table2_input);

	crossTable.crossProduct(table, importedTable);
	//unionTable.tableUnion(table, table2);
	//diffTable.tableUnion(table, table2);
	

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
	//unionTable.print();
	cout << "----------------------------------------------\n";	
	
	//wait();
	delete dbms1;

	return 0;
}



