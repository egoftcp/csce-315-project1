
#include <iostream>//|
#include "DBMS.h"

using namespace std;

int main(){

	DBMS* dbms1 = new DBMS(false, 7);
	dbms1->ExecuteTxtFile("testIn.txt");
	delete dbms1;
	cout<<"LEAVING MAIN!!!\n\n\n";	
		
	return 0;
}




int main1(){
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



