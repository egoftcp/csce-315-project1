// simple_example_4.cpp
#include<iostream>
#include<fstream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   
   ifstream inputFile("testinput.txt");
   string end,temp="";
   bool openToken=false;
   string content((istreambuf_iterator<char>(inputFile)),
				(istreambuf_iterator<char>()));
   char_separator<char> separator(" \n","\"()+<>=-;");
   vector<string> tokens;
   
   tokenizer<char_separator<char> > tok(content, separator);
   for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
   {
	   if(openToken==true)
	   {
			if(*beg=="<"||*beg==">"||*beg=="="||*beg=="\""||*beg=="("||*beg==")"||*beg=="-")
			{
				openToken=true;
				temp=temp+*beg;cout<<"saw "<<*beg<<" so openToken stays true and temp set to "<<temp<<endl;
			}
			else
			{
				tokens.push_back(temp);cout<<"Token   "<<temp<<endl;
				tokens.push_back(*beg);cout<<"Token   "<<*beg<<endl;
				temp="";
				openToken=false;
			}
	   }
	   else if(openToken==false)
	   {
			if(*beg=="<"||*beg==">"||*beg=="="||*beg=="\""||*beg=="("||*beg==")"||*beg=="-")
			{
				openToken=true;
				temp=*beg;cout<<"openToken was false and saw "<<*beg<<" so openToken set to true and temp set to "<<*beg<<endl;
			}
			else
			{
				tokens.push_back(*beg);cout<<"Token   "<<*beg<<endl;
				openToken=false;cout<<"saw "<<*beg<<" so openToken set to false and pushed "<<*beg<<endl;
			}
	   }
   }
	cout << "Press ENTER to quit";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

