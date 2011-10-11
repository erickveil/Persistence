#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
#define IOFILE "test.txt"

int touch(void);
int SaveStr(string str);

int main(void)
{
	fstream file;
	string sstring = "text to be saved.";

	SaveStr(sstring);
	return 0;
}

/*
	requires: fstream,iostream,string,cstring
*/
int SaveStr(string str)
{
	int ret=1;
	fstream file;

	// dynamicaly create an array of characters from the given string
	char* cstrloc;
	cstrloc = new char [str.size()+1];
	strcpy(cstrloc, str.c_str());

	// open the file for writing
	file.open(IOFILE,fstream::out);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed.\n";
		ret = 0;
	}
	else
	{
		file.write(cstrloc,str.size()+1);
	}
	//clean up and return
	file.close();
	delete[] cstrloc;
	return ret;
}

/*
	requires: fstream,iostream
*/
int touch(void)
{
	int ret=1;
	fstream file;
	file.open(IOFILE,fstream::in|fstream::out|fstream::app);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed.\n";
		ret = 0;
	}
	file.close();
	return ret;
}
