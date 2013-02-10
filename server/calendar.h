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
	string add(int date,cal_entry entry);
	string remove(int date,int start);
	string update(int date,cal_entry entry);
	string get(int date,int start);
	string get(int date);
	string get_number();
	string get_ith(int i);
};

/*Returns 
1 if date is in format mmddyy 
2 if date is in format ddmmyy
*/
int check_date(int date);

//Class containing data for all users
class calendar_users{
public:
	map< string , calendar> data_user;
	calendar get_data_user(string username);
	void put_data_user(string username,calendar cal);
};

/*Function to interact with the global calendar
@param: input_string is the string the client send
It parses the string and do corresponding changes in the calendar and 
return the corresponding messages whether of success or of any error
*/
string maintain_calendar(string input_string);
