#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
#define IOFILE "test.txt"

int touch(void);
int SaveStr(string str);
int LoadStr(string* str, int position);

typedef struct THING
{
	string str1;
	string str2;
	string str3;
}THING;

vector <THING> list;

int main(void)
{
	fstream file;
	int element =0;
	THING temp;

	file.open(IOFILE,fstream::in);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed.\n";
		exit(777);
	}
	while(!file.eof())
	{

		cout<<list.size()<<endl;

		getline(file,temp.str1);
		getline(file,temp.str2);
		getline(file,temp.str3);

		list.push_back(temp);

	}

	// output
	for (element = 0; element<list.size() ; ++element)
	{
		cout<<list[element].str1<<endl<<list[element].str2<<endl<<list[element].str3<<endl;
	}

	file.close();

	return 0;
}

int LoadFile(string* str, int position)
{
	fstream file;
	int ret = 0;
	file.open(IOFILE,fstream::in);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed.\n";
	}
	else
	{
		file.seekg(position);
		getline(file,*str);
		ret=file.tellg();
	}
	file.close();
	return ret;
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
