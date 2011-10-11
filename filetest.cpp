#include<fstream>
#include<iostream>
using namespace std;
#define IOFILE "test.txt"

int touch(void);

int main(void)
{
	fstream file;
	string sstring = "text to be saved.";

	touch();
	return 0;
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
