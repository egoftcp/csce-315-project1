#ifndef RELATION_H
#define RELATION_H

#include <string>
#include <iomanip>
#include "Attribute.h"

using namespace std;

//TODO: extrapolate definitions to .cpp 
//note: in notepadpp, press alt+3 , unfold: alt+shift+0

//TODO: move to utility class, looow priority 

class Relation {

public:

	string name;
	vector<string> primaryKeys; //attribute names
	//vector<string> values;
	vector<Attribute> columns;
	map<string, int> indices;
	//map<string, Attribute>::iterator start;
	int primaryKey;

	Relation(string input_name) {
		name = input_name;
	}
	
	Relation(string input_name, vector<string> input) {
		//wip
	}
	
	bool isUniqueColumn(Attribute column) {
		return true;  //wip
	}
	
	void addAttribute(string name, DataType type) {
		Attribute attr(name, type);
		columns.push_back(attr);
		indices[name] = (columns.size() - 1);
	}
	
	void addAttribute(Attribute attrToAdd) {
		columns.push_back(attrToAdd);
		indices[attrToAdd.getName()] = (columns.size() - 1);
	}

	void addSeveralAttributes(vector<string> name, vector<DataType> type) {
		for(int i = 0; i < name.size(); i++) {
			addAttribute(name[i], type[i]);
		}
	}
	
	void deleteAttribute(string name) {
		vector<Attribute>::iterator iter = columns.begin();

		columns.erase((iter + indices[name]));
		indices.erase(name);
	}

	void addTuple(vector<string> input) {
		int j = 0;
		for(int i = 0; i < columns.size(); i++) {
			columns[i].cells.push_back(input[j]);
			j++;
		}
	}

	vector<string> getTuple(int index) {
		vector<string> output;
		for(int i = 0; i < columns.size(); i++) {
			output.push_back(columns[i].cells[index]);
		}
		return output;
	}
	
	Attribute findAttribute(string input_name) {
		return columns[indices[input_name]];
	}
	Attribute* findAttributeP(string input_name) {
		return &columns[indices[input_name]];
	}
	
	
/*	int getIndex(string attribName, string uniqueValue){
		int col
		for(int i = 0; i < columns.size(); i++) {
			output.push_back(columns[i].cells[index]);
		}
		return output;
	}*/

	void setElement(int x, int y, string value) {
		columns[x].cells[y] = value;
	}

	string getName() {
		return name;
	}
	
	Relation selection(string input) {
		Relation result("a");
		
		return result;
	}
	
	Relation projection(string input) {
		Relation result("b");
		
		return result;
	}
	
	string stringify() {
		string table = "(";
		int j = 0;	
		for(int i = 0; i < columns.size(); i++) {
			j++;
			if( j == columns.size() ) {
				table = table + columns[i].getName() + " " + columns[i].getType() + ")\n";
			} else {
				table = table + columns[i].getName() + " " + columns[i].getType() + ", ";
			}
		}
	
		for(int i = 0; i < getHeight(); i++) {
			table = table + "(";	
			
			for(int j = 0; j < columns.size(); j++) {
			
				if(j == (columns.size()-1)) {
					if( columns[j].isInt() ) {
						table = table + columns[j].cells[i] + ")";
					} else {
						table = table + "\"" + columns[j].cells[i] + "\")";
					}
				} else {
					if( columns[j].isInt() ) {
						table = table + columns[j].cells[i] + ", ";
					} else {
						table = table + "\"" + columns[j].cells[i] + "\", ";
					}
				}				
			
			}
			table = table + '\n';
		}
		table = table + "\n";
		return table;
	}
	
	//void update(vector< pair<string colName, string newVal> > setList, condition_tree/list)
	
	void print() {
		//Prints the header (name of attributes)
		for(int i = 0; i < columns.size(); i++) {
			cout << setw (19)<<columns[i].getName();
		}
		cout << endl;
		//Prints the tuples (elements/cells)
		for(int i = 0; i < columns[0].cells.size(); i++) {
			for(int j = 0; j < columns.size(); j++) {
				cout << setw (19)<<columns[j].cells[i];
			}
			cout << endl;
		}
	}
	
	void parseHeader(string line) {
		string temp = "";
		string name = "";
		string varCharLength = "";
	
		for(int i = 0; i < line.size(); i++) {
			if( isalpha(line[i]) ) {
				while( isalpha(line[i]) ) {
					name = name + line[i];
					i++;
				}

				i++;
				while( isalpha(line[i]) ) {
					temp = temp + line[i];
					i++;
				}
			
				if( strcmp(temp.c_str(), "INTEGER") == 0) {
					DataType type(true);
					addAttribute(name, type);
				} else {
					if( strcmp (temp.c_str(), "VARCHAR") == 0 ) {
						i++;
						while( Helpers::isNum(line[i]) ) {
							varCharLength = varCharLength + line[i];
							i++;
						}
						DataType type(atoi(varCharLength.c_str()));
						addAttribute(name, type);
					} else { cout << '[' + i + "] " "ERROR IN PARSING\n"; }
				}
				temp = "";
			}
			//i = i++;
			name = "";
			varCharLength = "";
		}
	}
	
	void parseTuples(string line) {
		vector<string> cells;
		string temp = "";
		for(int i = 0; i < line.size(); i++) {
			if( line[i] == '\"' ) {
				i++;
				while(line[i] != '\"' ) {
					temp = temp + line[i];
					i++;
				}
				cells.push_back(temp);
				temp = "";
			} else {
				if( Helpers::isNum(line[i]) ) {
					while(Helpers::isNum(line[i])) {
						temp = temp + line[i];
						i++;
					}
					cells.push_back(temp);				
					temp = "";
				}
			}
			if(line[i] == ')') {
				break;
			}
		}
		
		if(cells.size() != 0) {
			addTuple(cells);
		}
	}
	
	int getHeight() {
		return (columns[0].getSize());
	}
	
	
	Relation Relation::operator+(const Relation& right) {
		Relation result = *this;
		bool equal; 	
	}
	
	void selection(Relation table, string input) {
		
	}
	
	void projection(Relation table, string input) {
		
	}
	
	void crossProduct(Relation table1, Relation table2) {
		vector<string> names;
		vector<DataType> types;
		
		for(int i = 0; i < table1.columns.size(); i++) {
			names.push_back( table1.columns[i].getName() );
			types.push_back( table1.columns[i].type );
		}
		for(int i = 0; i < table2.columns.size(); i++) {
			names.push_back( table2.columns[i].getName() );
			types.push_back( table2.columns[i].type );
		}
		addSeveralAttributes(names, types);

		vector<string> first;
		vector<string> second;
		vector<string> data;

		for(int i = 0; i < table1.getHeight(); i++) {

			for(int j = 0; j < table2.getHeight(); j++) {
				first = table1.getTuple(i);
				second = table2.getTuple(j);

				for(int m = 0; m < first.size(); m++) {
					data.push_back(first[m]);
				}

				for(int k = 0; k < second.size(); k++) {
					data.push_back(second[k]);
				}
				
				addTuple(data);
				data.clear();
				first.clear();
				second.clear();
			}
		}
	}
	
	void deleteTuple(int index) {
		
		for(int i = 0; i < columns.size(); i++) {
			vector<string>::iterator iter = columns[i].cells.begin() + index;
			columns[i].cells.erase(iter);		
		}
	}

	bool matchingAttributes(Relation table1, Relation table2) {
	
		if(table1.columns.size() == table2.columns.size()) {
			bool hasMatch;


			for(int i = 0; i < table1.columns.size(); i++) {
				hasMatch = false;
				for(int j = 0; j < table2.columns.size(); j++) {
					if(strcmp(table1.columns[i].getName().c_str(), table2.columns[j].getName().c_str()) == 0) {
						hasMatch = true;
					}
				}
				if(hasMatch == false) {
					return false;
				}
			}

			return true;

		} else {
			return false;
		}
	
		//return true;
	}

	vector<string> constructTupleFromIndex(int index) {
		vector<string> tuple;
		for(int i = 0; i < columns.size(); i++) {
			tuple.push_back(columns[i].cells[index]);
		}
		
		
		cout << "***constructTupleFromIndex***\n";
		for(int i = 0; i < tuple.size(); i++) {
			cout << tuple[i] << '\t';
		}
		cout << "\n========================\n";
		
		return tuple;
	}

	bool equalTuples(vector<string> tuple1, vector<string> tuple2) {
		if(tuple1.size() == tuple2.size()) {
			bool hasMatch;
			for(int i = 0; i < tuple1.size(); i++) {
				hasMatch = false;
				for(int j = 0; j < tuple2.size(); j++) {
					if(strcmp(tuple1[i].c_str(), tuple2[j].c_str()) == 0) {
						hasMatch = true;
					}
				}

				if(hasMatch == false) {
					return false;
				}

			}

			return true;

		} else {
			return false;
		}
	}
	
	
	int tableUnion(Relation table1, Relation table2) {
		if(!matchingAttributes(table1, table2)) {
			cout << "Incompatible tables for Union operation\n";
			return -1;
		} else {
			
			cout << "Made it here!\n";
			char a;
			cin >> a;
			
			vector<string> tuple1;
			for(int i = 0; i < table1.getHeight(); i++) {
				//addTuple(table1.constructTupleFromIndex(i));
				
				for(int j = 0; j < table1.columns.size(); j++) {
					
					tuple1.push_back( table1.columns[j].cells[i] );
				}
				for(int k = 0; k < tuple1.size(); k++) {
					cout << tuple1[k] << '\t';
				}
				addTuple(tuple1);
				tuple1.clear();
			}
						
			bool alreadyInTable1;
			int index;

			for(int i = 0; i < table2.getHeight(); i++) {
				alreadyInTable1 = false;
				for(int j = 0; j < table1.getHeight(); j++) {

					if(equalTuples(table2.constructTupleFromIndex(i), table1.constructTupleFromIndex(j))) {
						alreadyInTable1 = true;
					}

				}

				if(alreadyInTable1) {
					//do nothing
				} else {
					addTuple(table2.constructTupleFromIndex(i));
				}
			}
		}
		return 0;
	}

	int tableDifference(Relation table1, Relation table2) {
		//table1 - table2

		if(!matchingAttributes(table1, table2)) {
			cout << "Incompatible tables for Difference operation\n";
			return -1;
		} else {


			for(int i = 0; i < table1.getHeight(); i++) {

				for(int j = 0; j < table2.getHeight(); j++) {

					if(equalTuples(table1.constructTupleFromIndex(i), table2.constructTupleFromIndex(j))) {
						deleteTuple(i);
					}
				}
			}
		}
	}
};

#endif


