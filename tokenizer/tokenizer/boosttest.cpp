
#include<iostream>
#include<fstream>
#include<boost/tokenizer.hpp>
#include<string>
#include<ctype.h>

using namespace std;

//int main(){
vector<string> dbTokens()
{

   using namespace boost;
   
   ifstream inputFile("testinput.txt");
   string end,temp="";
   bool openSymbol=false,closeSymbol=false,openQuote=false;
   string content((istreambuf_iterator<char>(inputFile)),(istreambuf_iterator<char>()));
   char_separator<char> separator(" \n","\"()+<>=-;,");
   vector<string> tokens;
   tokenizer<char_separator<char> > tok(content, separator);


   for(tokenizer<char_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
   {
	   if(openQuote==true)
	   {
			if(*beg=="\"")
			{
				tokens.push_back(temp);cout<<"["<<temp<<"]";
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=false;
			}
			else
				if(temp=="")
					temp=*beg;
				else
					temp=temp+" "+*beg;
	   }
	   else if(openSymbol==true)
	   {
			if(*beg=="\"")
			{
				tokens.push_back(temp);cout<<"["<<temp<<"]";
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=true;
			}
			else if(*beg=="<"||*beg=="="||*beg=="-")
			{
				openSymbol=true;
				temp=temp+*beg;//cout<<"saw "<<*beg<<" so openSymbol stays true and temp set to "<<temp<<endl;
			}
		   else if(*beg==";")
		   {
			   	closeSymbol=false;
				openSymbol=false;
				tokens.push_back(*beg);cout<<"["<<*beg<<"]"<<endl;
				temp="";
		   }
			else
			{
				tokens.push_back(temp);cout<<"["<<temp<<"]";
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=false;
			}
	   }
	   else if(closeSymbol==true)
	   {
		   if(*beg=="\"")
			{
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=false;
			}
		   else if(*beg==">"||*beg=="="||*beg==")"||*beg=="-")
			{
				closeSymbol=true;
				temp=temp+*beg;//cout<<"closeSymbol was true and saw "<<*beg<<" so closeSymbol kept true and temp set to "<<temp<<endl;
			}
		   else if(*beg=="<"||*beg=="="||*beg=="-")
			{
				closeSymbol=false;
				openSymbol=true;
				tokens.push_back(temp);
				temp=*beg;//cout<<"closeSymbol was true but saw "<<*beg<<" so closeSymbol now false, openSymbol set to true and pushed "<<*beg<<endl;

			}
		   else if(*beg==";")
		   {
			   	closeSymbol=false;
				openSymbol=false;
				tokens.push_back(*beg);cout<<"["<<*beg<<"]"<<endl;
				temp="";
		   }
		   else
			{
				tokens.push_back(temp);cout<<"["<<temp<<"]";
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				closeSymbol=false;//cout<<"closeSymbol was true and saw "<<*beg<<" so closeSymbol set to false and pushed "<<*beg<<endl;
				temp="";
			}
	   }
	   else
	   {
		   if(*beg=="\"")
		   {
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				temp="";
				openSymbol=false;
				closeSymbol=false;
				openQuote=true;//cout<<"openQuote was false and saw"<<*beg<<" so set openQuote to true";
		   }
		   else if(*beg=="<"||*beg=="="||*beg=="-")
			{
				openSymbol=true;
				temp=temp+*beg;//cout<<"openSymbol was false and saw "<<*beg<<" so openSymbol set to true and temp set to "<<temp<<endl;
			}
		   else if(*beg==">"||*beg=="="||*beg==")"||*beg=="-")
			{
				closeSymbol=true;
				temp=*beg;//cout<<"closeSymbol was false and saw "<<*beg<<" so closeSymbol set to true and temp set to "<<temp<<endl;
			}
		   else if(*beg==";")
		   {
			   	closeSymbol=false;
				openSymbol=false;
				tokens.push_back(*beg);cout<<"["<<*beg<<"]"<<endl;
				temp="";
		   }

		   else
		   {
				closeSymbol=false;
				openSymbol=false;
				tokens.push_back(*beg);cout<<"["<<*beg<<"]";
				temp="";
		   }
	   }
   }
   return tokens;
//	cout << "Press ENTER to quit";
//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
	vector<string> testvector(dbTokens());
	for (vector<string>::iterator i = testvector.begin();i != testvector.end();++i)
	{
    cout << *i << endl;
	}
}

