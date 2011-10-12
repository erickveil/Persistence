#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
#define IOFILE "test.txt"

int touch(void);
int SaveStr(string str);
int LoadFile(void);
void DeleteFile(void);
int GetFileSize(fstream* file);

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

	DeleteFile();

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
		// one getline statement for each member of the structure
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

/*
	LoadFile()
	Erick Veil
	10-11-11
	pre: IOFILE constant defined as the name of the file to load,
	a structure and its members, a global vector called list
	post: vector should be of type THING structures, the members of
	which are loaded with the contents of IOFILE
	note: IOFILE, THING, list, and str1 member function of THING
	will all have to be customised based on the program this function is
	included in.
	TODO: make this a more modular function to be used in code with less
	modification.
	requires: fstream, iostream
*/
int LoadFile(void)
{
	THING temp;
	fstream file;
	file.open(IOFILE,fstream::in);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed.\n";
		exit(777);
	}
	while(!file.eof())
	{
		// one getline statement for each member of the structure
		getline(file,temp.str1);
		list.push_back(temp);
	}
	file.close();
	return list.size();
}


/*
	SaveStr()
	Erick VEil
	10-11-11
	pre: a string to be saved to a file, a constant IOFILE
	with the name of the file
	post: appends the string to the end of the file with a
	newline character after it. returns either 0 if failed,
	or the size of the string written.
	requires: fstream,iostream,string,cstring
*/
int SaveStr(string str)
{
	int ret;
	fstream file;
	ret=str.size()+1;

	// dynamicaly create an array of characters from the given string
	char* cstrloc;
	cstrloc = new char [ret];
	strcpy(cstrloc, str.c_str());
	cstrloc[ret-1]='\n';

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
		file.write(cstrloc,ret);
	}
	//clean up and return
	file.close();
	delete[] cstrloc;
	return ret;
}

/*
	GetFileSize()
	Erick Veil
	10-11-11
	pre: pointer to an open file
	post: returns the size of a file in bytes
	requires fstream
*/
int GetFileSize(fstream* file)
{
	int size;
	file->seekg(0,ifstream::end);
	size=file->tellg();
	file->seekg(0);
	return size;
}

/*
	DeleteFile()
	Erick Veil
	10-11-11
	pre: a constant IOFILE with the name of the file
	Clears a file of all its contents.
	requires fstream
*/
void DeleteFile(void)
{
	ofstream file;
	file.open(IOFILE,ios::trunc);
	file.close();
}

/*
	touch()
	Erick Veil
	10-11-11
	pre: a constant IOFILE with the name of the file
	post: returns 1 if successful, 0 if not
	Acts as a unix touch command, creating the file if
	it does not exist.
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
