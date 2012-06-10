#ifndef RELATION_H
#define RELATION_H

#include <string>
#include "Attribute.h"

using namespace std;

//TODO: extrapolate definitions to .cpp 
//note: in notepadpp, press alt+3 , unfold: alt+shift+0

//TODO: move to utility class, looow priority 
bool isNum(char input) {
	if(input == '-' || input == '0' ||
	   input == '1' || input == '2' ||
	   input == '3' || input == '4' ||
	   input == '5' || input == '6' ||
	   input == '7' || input == '8' ||
	   input == '9' ) {
		return true;
	}
	else {
		return false;
	}
}



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
	
		for(int i = 0; i < columns[0].getSize(); i++) {
			table = table + "(";	
			j = 0;
			for(int k = 0; k < columns.size(); k++) {
				if(j == columns[0].getSize()) {
					if( columns[k].isInt() ) {
						table = table + columns[k].getElement(i) + ")\n";
					} else {
						table = table + "\"" + columns[k].getElement(i) + "\")\n";
					}
				} else {
					if( columns[k].isInt() ) {
						table = table + columns[k].getElement(i) + ", ";
					} else {
						table = table + "\"" + columns[k].getElement(i) + "\", ";
					}
				}	
				j++;
			}
		}
		table = table + "\n";
		return table;
	}
	
	//void update(vector< pair<string colName, string newVal> > setList, condition_tree/list)
	
	void print() {
		
		//Prints the header (name of attributes)
		for(int i = 0; i < columns.size(); i++) {
			cout << columns[i].getName() << '\t';
		}
		cout << '\n';

		for(int i = 0; i < columns[0].cells.size(); i++) {
			for(int j = 0; j < columns.size(); j++) {
				cout << columns[j].cells[i] << '\t';
			}
			cout << '\n';
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
						while( isNum(line[i]) ) {
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
				if( isNum(line[i]) ) {
					while(isNum(line[i])) {
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

};

#endif


