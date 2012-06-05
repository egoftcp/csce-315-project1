// simple_example_4.cpp
#include<iostream>
#include<boost/tokenizer.hpp>
#include<string>

int main(){
   using namespace std;
   using namespace boost;
   
   string s = "This (is),  a + test";
   string end;
   char_separator<char> separator( "", "()+-" );
   tokenizer<char_separator<char> > tok(s);
   for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
       cout << *beg << "\n";
   }
   cin>>end;
}