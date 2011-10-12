/*
    CH11PC4
    Inventory
    Erick Veil
    9-28-11
    The program should use an array of at least 20 structures.
    It should let the user enter data into the array, change
    the contents of any element, and display all the data
    stored in the array. The program should have a menu-driven
    user interface.
*/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <limits.h>
#include <fstream>
#include <cstring>
using namespace std;

#define PAGESIZE 16
#define IOFILE "inventory.txt"

typedef struct RECORD
{
    string decrip, date;
	int qty;
    double cost, price;
}RECORD;

vector <RECORD> list;

enum {NEW=1,EDIT,SHOW,QUIT};
enum {DESC=1,QTY,COST,PRICE,DATE};

void DisplayMenu(void);
RECORD PromptRecordEntry(bool newrec, int recordnumber=0);
void DisplayRecordList(void);
void DisplayRecord(RECORD entry);
int PromptValidInt(int low, int high, string prompt);
int PromptValidInt(int low, string prompt);
string PromptValidString(string prompt);
double PromptValidDouble(double low, string prompt);
int GetYN(string msg);
void Pause(void);
string ConvertLineLowerCase(string line);

void OpenFile(fstream* fstrm);
void SaveVector(fstream* fstrm);
int LoadFile(void);
void DeleteFile(void);
int SaveStr(string str);
void SaveFile();

int main(void)
{
    int selection;
	LoadFile();

    do{
        DisplayMenu();
        switch(PromptValidInt(NEW, QUIT, "\n\tPlease enter a number from the menu: "))
        {
            case NEW:
                list.push_back(PromptRecordEntry(1));
                break;
            case EDIT:
                DisplayRecordList();
                if(list.size()!=0)
                {
                    selection=PromptValidInt(0,list.size()-1,"\n\n\tEnter the number of the record to edit: ");
                    list[selection]=PromptRecordEntry(0,selection);
                }
                DeleteFile();
                break;
            case SHOW:
                DisplayRecordList();
                if(list.size()!=0)
                    DisplayRecord(list[PromptValidInt(0,list.size()-1,"\n\n\tEnter the number of the record to display: ")]);
                break;
            case QUIT:
                Pause();
                exit(EXIT_SUCCESS);
                break;
        }
    }while(GetYN("\n\tBack to main menu? (Y/N): "));
    Pause();
    return 0;
}

/*
	SaveFile()
	Erick Veil
	10-11-11
	pre: IOFILE as the input file name, list as a vector
	of structures
	post: converts all members of each structure in the vector to
	strings, and appends them to the target file.
*/
void SaveFile()
{
	fstream file;
	stringstream out;
	string temp;
	OpenFile(&file);
	for(int element=0;element<list.size();++element)
	{
		//members of the structure
		SaveStr(list[element].decrip);
		// converts int to string before saving
		out<<list[element].qty;
		temp=out.str();
		SaveStr(temp);
		// works on floats
		out<<list[element].cost;
		temp=out.str();
		SaveStr(temp);

		out<<list[element].price;
		temp=out.str();
		SaveStr(temp);

		SaveStr(list[element].date);
	}
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
	LoadFile()
	Erick Veil
	10-11-11
	pre: IOFILE constant defined as the name of the file to load,
	a structure and its members, a global vector called list
	post: vector should be of type THING structures, the members of
	which are loaded with the contents of IOFILE
	note: and str1 member function of THING
	will all have to be customised based on the program this function is
	included in.
	requires: fstream, iostream
*/
int LoadFile(void)
{
	RECORD temp;
	fstream file;
	string temp_in;
	file.open(IOFILE,fstream::in);
	if (file.fail())
	{
		cout<<"\nFile read\\write failed: LoadFile()\n";
		exit(777);
	}
	while(!file.eof())
	{
		// one getline statement for each member of the structure
		getline(file,temp.decrip);
		getline(file,temp_in);
		temp.qty=atoi(temp_in.c_str());
		getline(file,temp_in);
		temp.cost=atof(temp_in.c_str());
		getline(file,temp_in);
		temp.price=atof(temp_in.c_str());
		getline(file,temp.date);
		list.push_back(temp);
	}
	file.close();
	return list.size();
}

/*
    Pause()
    Erick Veil
    10-01-11
    Simple user continued pause
*/
void Pause(void)
{
    string enter;
    cout<<"\n\n\tPress Enter to continue..";
    getline(cin,enter);
}

/*
    DisplayMenu()
    Initial output including a title and main menu
*/
void DisplayMenu(void)
{
    cout<<"\n\t*** Inventory Management ***"<<endl<<"\tby Erick Veil"<<endl;
    cout<<endl<<"\t"<<NEW<<". Enter a new item\n\t"<<EDIT<<". Edit an item\n\t"<<SHOW<<". View an item's information\n\t"<<QUIT<<". Quit\n";
}

/*
    PromptValidInt()
    Erick Veil
    9-30-11
    pre: low is the lowest allowed value to be input. High is the highest.
        prompt is the output prompt given
    post: validated input as an integer within the specified range and
        returns the result
    exception:  exits with an error if low is greater than high
    prereqs: iostream, string, sstream, ctdlib
*/
int PromptValidInt(int low, int high, string prompt)
{
    string input;
    int ret;

    if(low>high)
    {
        cout<<"ERROR: low/high switch in module: PromptValidInt()";
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        stringstream inputstream(input);
        if(
            (inputstream >> ret) &&
            (ret <= high) &&
            (ret >=low)
            )
            break;
        cout<<"\tYou must enter an integer between "<<low<<" and "<<high<<": ";
    }
    return ret;
}

/*
    PromptValidInt()
    Erick Veil
    10-05-11
	Overloaded for optional upper limits
    pre: low is the lowest allowed value to be input.
        prompt is the output prompt given
    post: validated input as an integer within the specified range and
        returns the result
    exception:  exits with an error if low is greater than high
    prereqs: iostream, string, sstream, ctdlib
*/
int PromptValidInt(int low, string prompt)
{
    string input;
    int ret;

    if(low>INT_MAX)
    {
        cout<<"ERROR: low value for int exceeds maximum: PromptValidInt()";
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        stringstream inputstream(input);
        if(
            (inputstream >> ret) &&
            (ret <= INT_MAX) &&
            (ret >=low)
            )
            break;
        cout<<"\tYou must enter an integer greater than "<<low<<": ";
    }
    return ret;
}

/*
    PromptValidDouble()
    Erick Veil
    10-01-11
    pre: low is the lowest possible value allowed to be entered by
        the user. prompt is the input prompt displayed
    post: a prompt is displayed and the user required to enter a double
        input is validated to be a numeric value within the specified
        scope and returned
*/
double PromptValidDouble(double low, string prompt)
{
    string input;
    double ret;

    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        stringstream inputstream(input);
        if(
            (inputstream >> ret) &&
            (ret >= low)
            )
            break;
        cout<<"\tYou must enter a decimal value of at least "<<low<<": ";
    }
    return ret;
}

/*
    PromptRecordEntry()
    Erick Veil
    10-01-11
    pre: if newrec is 1, it indicates that this is a new, blank record.
        if 0, it indicates that it is an existing record. recordnumber
        is only required if newrec is 0, and defaults to the first
        record
    post: if newrec is 1, it lists the available fields for the record,
        then sets newrec to 0. If newrec is 0, it displays whatever
        information is stored in the existing record (default is
        record 0). The module then prompts the user for a field to
        edit the data for and allows data entry. New records cannot be
        left with empty fields.
*/
RECORD PromptRecordEntry(bool newrec, int recordnumber)
{
    RECORD entry;
    entry.cost= -1.0;
	entry.price= -1.0;
	entry.qty= -1;
    bool incomplete;
    if(!newrec)
        entry=list[recordnumber];

    do
    {
        if(newrec)
        {
				cout<<"\n\tSelect field to enter:\n\t"<<DESC<<". Description\n\t"<<QTY<<". Quantity on hand\n\t"
				<<COST<<". Wholsale Cost\n\t"<<PRICE<<". Retail Price\n\t"<<DATE<<". Date Added\n";
            newrec=0;
        }
        else
        {
            DisplayRecord(entry);
        }
        do
        {
            switch(PromptValidInt(DESC,DATE,"\n\tEnter field number: "))
            {
                case DESC:
                    entry.decrip=PromptValidString("\n\tEnter product description: ");
                    break;
                case QTY:
                    entry.qty=PromptValidInt(0,"\n\tEnter the quantity on hand: ");
                    break;
                case COST:
                    entry.cost=PromptValidDouble(0,"\n\tEnter the wholsale cost of the item: ");
                    break;
                case PRICE:
                    entry.price=PromptValidDouble(0,"\n\tEnter the retail price of the item: ");
                    break;
                case DATE:
                    entry.date=PromptValidString("\n\tEnter the date entered: ");
                    break;
            }
        }while(GetYN("\n\tEnter another field? (Y/N): "));
        if(entry.decrip.empty() ||
            entry.date.empty() ||
			entry.qty<0.0 ||
            entry.cost<0.0 ||
            entry.price<0.0
            )
        {
            cout<<"\n\tAll fields must be complete.\n";
            incomplete=1;
        }
        else
            incomplete=0;
    }while(incomplete);
    return entry;
}

/*
    PromptValidString()
    Erick Veil
    10-01-11
    pre: a string to prompt the user for input
    post: recieves a string from the user and validates
        that it is not empty. Returns the valid string.
*/
string PromptValidString(string prompt)
{
    string input;
    while(true)
    {
        cout<<prompt;
        getline(cin,input);
        if(!input.empty())
            break;
        cout<<"\n\tYou cannot have empty values.";
    }
    return input;
}

/*
    DisplayRecordList()
    Erick Veil
    10-01-11
    post: Outputs a vector filled with records. The list is
    made up of record number, the last name, then the forst
    name for each record. Large vectors are output in pages
    of PAGESIZE numbers of entries, requiring the user to
    manualy continue.
*/
void DisplayRecordList(void)
{
    string enter;
    cout<<"\n\tRecord List: ";
    if(list.size()==0)
        cout<<"\n\tThere are no records to display.";
    else
    {
        for(unsigned int element = 0; element < list.size(); ++element)
        {
            cout<<"\n\t"<<element<<". "<<list[element].decrip;
            if(element+1%PAGESIZE == 0)
            {
                cout<<"\n\tPress enter to continue..";
                getline(cin,enter);
            }
        }
    }
}

/*
    DisplayRecord()
    Erick Veil
    10-01-11
    pre: a RECORD structure
    post: outputs the content of a RECORD
*/
void DisplayRecord(RECORD entry)
{
	double cost = entry.cost, price = entry.price;
	int qty = entry.qty;
    if(cost==-1.0)
        cost = 0.0;
	if(price==-1.0)
        price = 0.0;
	if(qty==-1.0)
        qty = 0;
    cout<<fixed<<setprecision(2)
        <<"\n\t"<<DESC<<". Description:\t\t"<<entry.decrip
        <<"\n\t"<<QTY<<". Quantity on hand:\t\t"<<qty
        <<"\n\t"<<COST<<". Wholsale Cost:\t\t$"<<cost
        <<"\n\t"<<PRICE<<". Retail Price:\t\t$"<<price
        <<"\n\t"<<DATE<<". Date Entered:\t\t"<<entry.date
        <<endl;
}

/*
    GetYN()
    Erick Veil
    9-15-11
    pre: message that will be displayed as a prompt
    post: Prompts the user for input, accepting only a y or an n.
        Returns 1 if y, 0 if n.
	10-05-11
	Added support for entering "yes" or "no"
*/
int GetYN(string msg)
{
    string input;
    int retval=0;

    while (true)
    {
        cout<<msg;
        getline(cin,input);
        if(input.length()==1)
        {
            if(input[0]=='y'||input[0]=='Y'||input[0]=='1')
            {
                retval = 1;
                break;
            }
            else if(input[0]=='n'||input[0]=='N'||input[0]=='0')
            {
                retval = 0;
                break;
            }
        }
		else
		{
			ConvertLineLowerCase(input);
			if(input == "yes")
			{
                retval = 1;
                break;
            }
			else if(input== "no")
			{
                retval = 0;
                break;
            }
		}
        cout<<"\n\tYour input is not valid. Please enter a Y or N: ";
    }
    return retval;
}

/*
    OpenFile()
    Erick Veil
    9-21-11
    pre: provide a pointer to a file object and the name of a file
    post: opens the file and validates that it was opened. exits the program if not
    10-11-11: ammended to use IOFILE as its filename
*/
void OpenFile(fstream* fstrm)
{
	fstrm->open(IOFILE,fstream::in|fstream::out);
    if(fstrm->fail())
    {
        cout<<"\n\nfile open failed. aborting.\n\n";
        exit(777);
    }
}

void SaveVector(fstream* fstrm)
{
	stringstream num;
	fstrm->seekg(0);
	for(unsigned int element = 0;element < list.size(); ++element)
	{
		fstrm->write(list[element].decrip.c_str(),list[element].decrip.size());
		num<<list[element].qty;
		fstrm->write(num.str().c_str(),sizeof(num));
		num<<list[element].cost;
		fstrm->write(num.str().c_str(),sizeof(num));
		num<<list[element].price;
		fstrm->write(num.str().c_str(),sizeof(num));
		fstrm->write(list[element].date.c_str(),list[element].date.size());
	}
}

void LoadVector(fstream* fstrm)
{

	int legnth;
	char* buffer;
	string buffy;

	legnth = fstrm->tellg();
	buffer = new char [legnth];
	fstrm->seekg(0);
	//for(unsigned int element = 0;element < list.size(); ++element)
	//{
		fstrm->read(buffer,legnth);
	//}
	buffy=buffer;
	cout<<buffy;
}

/*
    ConvertLineLowerCase()
    Erick Veil
    9-21-11
    pre: a string
    post: converts every letter of the line to lower case. Returns the altered string
*/
string ConvertLineLowerCase(string line)
{
    unsigned int t;
    string newstr="";
    for(t=0;t<line.size();++t)
    newstr+=tolower(line[t]);
    return newstr;
}
