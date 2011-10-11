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
void DeleteFile(void);

typedef struct THING
{
	string str1;

}THING;

vector <THING> source;
vector <THING> list;

int main(void)
{
	fstream file;
	int element =0;
	THING temp;

	void DeleteFile(void);

	// load up the source vector
	for(element=0;element<=3;++element)
	{
		getline(cin,temp.str1);
		source.push_back(temp);
	}


	//saving the file
	for(int t=0;t<source.size();++t)
	{
		SaveStr(source[t].str1);

	}


	// Loading the file
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


		list.push_back(temp);
	}

	// output
	for (element = 0; element<list.size() ; ++element)
	{
		cout<<list[element].str1<<endl;
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
	cstrloc = new char [str.size()+1];
	strcpy(cstrloc, str.c_str());
	cstrloc[str.size()]='\n';

	// open the file for writing
	file.open(IOFILE,fstream::out|fstream::app);
	//file.open(IOFILE,fstream::out);
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

void DeleteFile(void)
{
	fstream file;
	file.open(IOFILE,fstream::trunc);
	//SaveStr("");
	file.close();
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
