#include<fstream>
using namespace std;

int main(void)
{
	fstream file;
	string sstring = "text to be saved.";
	
	file.open("test.txt",fstream::in|fstream::out|fstream::app);
	file.write(sstring.c_str(),sizeof(sstring.c_str()));
	file.close();
	return 0;
}