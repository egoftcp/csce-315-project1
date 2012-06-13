#ifndef CONDCONJCOMPOP_H
#define CONDCONJCOMPOP_H

#include "Relation.h"
#include "Helpers.h"

enum Operation { Equality=0, NonEquality, LessThanEqual, GreaterThanEqual, LessThan, GreaterThan}; // ==, !=, <, >, <=, >=

class Operand{
public:
	bool isAttribute;
	string val; //either attribute name or literal
};


class Condition;
class Conjunction;
class Comparison;

class Condition{
public:
	vector<Conjunction> conjunctions;
	bool passes(Relation* relation, int tupleIndex);
};

class Conjunction{
public:
	vector<Comparison> comparisons;
	bool passes(Relation* relation, int tupleIndex);
};

class Comparison{
public:
	bool isCondition;
	Condition cond;
	Operand operand1;
	Operation op;
	Operand operand2;
	bool passes(Relation* relation, int tupleIndex);
};

bool Condition::passes(Relation* relation, int tupleIndex){ //only 1 conjuntion must pass for condition to be true
	for(int i =0; i<conjunctions.size(); i++){
			if(conjunctions[i].passes(relation, tupleIndex)){
				return true;
			}
	}
	return false;
}

bool Conjunction::passes(Relation* relation, int tupleIndex){ //only 1 comparison must fail for condition to be false
	for(int i =0; i<comparisons.size(); i++){
			if( !(comparisons[i].passes(relation, tupleIndex)) ){
				return false;
			}
	}
	return true;
}

bool Comparison::passes(Relation* relation, int tupleIndex){
	if(isCondition){
		return cond.passes(relation, tupleIndex);
	}
	else{
		bool intFlag;
		int ival1, ival2;
		string val1, val2;
		if(operand1.isAttribute){
			intFlag = relation->findAttribute(operand1.val).type.isInt();
			val1=relation->findAttribute(operand1.val).cells[tupleIndex];
			if(intFlag) ival1=Helpers::stringToInt(val1);
		}else{
			val1=operand1.val;
		}
		if(operand2.isAttribute){
			val2=relation->findAttribute(operand2.val).cells[tupleIndex];
		}else{
			val2=operand2.val;
			if(intFlag) ival2=Helpers::stringToInt(val2);
		}
		if(!intFlag){
			switch (op){
				case 0:
					return val1==val2;
					break;
				case 1:
					return val1!=val2;
					break;
				case 2:
					return val1<=val2;
					break;
				case 3:
					return val1>=val2;
					break;
				case 4:
					return val1<val2;
					break;
				case 5:
					return val1>val2;
					break;
			}
		}else{
			switch (op){
				case 0:
					return ival1==ival2;
					break;
				case 1:
					return ival1!=ival2;
					break;
				case 2:
					return ival1<=ival2;
					break;
				case 3:
					return ival1>=ival2;
					break;
				case 4:
					return ival1<ival2;
					break;
				case 5:
					return ival1>ival2;
					break;
			}
		}
	}
}


#endif

