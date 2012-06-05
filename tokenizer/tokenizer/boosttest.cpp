// simple_example_4.cpp
#include<iostream>
#include<fstream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   
   ifstream inputFile("testinput.txt");
   string end;
   string content((istreambuf_iterator<char>(inputFile)),
				(istreambuf_iterator<char>()));
   char_separator<char> separator(" \n","\"()+<>=-;");
   vector<string> tokens;
   
   tokenizer<char_separator<char> > tok(content, separator);
   for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
   {

		   tokens.push_back(*beg);
	   cout << tokens.back() << "\n";
   }
   
   
	cout << "Press ENTER to quit";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

