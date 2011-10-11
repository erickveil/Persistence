#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
#define IOFILE "test.txt"

int touch(void);
int SaveStr(string str);
string LoadStr(void);

int main(void)
{
	fstream file;

	string sstring = LoadStr();
	cout<<sstring;

	sstring = LoadStr();
	cout<<sstring;


	return 0;
}

string LoadStr(void)
{
	fstream file;
	string buffer;
	file.open(IOFILE,fstream::in);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed.\n";
	}
	else
	{
		getline(file,buffer);
	}
	file.close();
	return buffer;
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
	cstrloc = new char [str.size()];
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
		file.write(cstrloc,str.size());
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
