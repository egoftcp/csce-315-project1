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
   char_separator<char> separator( "", "()+-" );



   

   tokenizer<char_separator<char> > tok(content);
   for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
   {
       cout << *beg << "\n";
   }
   
   cout<<"\nPress Enter to Exit...";
   cin>>end;
}

