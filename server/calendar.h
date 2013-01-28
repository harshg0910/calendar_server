#include<string>
#include<map>
#include<list>
#include<iostream>
#include<sstream>
using namespace std;

class cal_entry{
public:
	int start;
	int end;
	string event;
	cal_entry(int,int,string);
	bool operator==(cal_entry);
};

class calendar{
	/*	
	This map contains date as the key and list of 
	cal_entry corresponding to each date
	   */

	map< int,list<cal_entry> > data;
public:
	bool add(int date,cal_entry entry);
	int remove(int date,int start);
	int update(int date,cal_entry entry);
	string get(int date,int start);
	string get(int date);
};

/*Returns 
1 if date is in format mmddyy 
2 if date is in format ddmmyy
*/
int check_date(int date);

