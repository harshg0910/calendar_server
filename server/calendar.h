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

public:
	map< int,list<cal_entry> > data;
	string add(int date,cal_entry entry);
	string remove(int date,int start);
	string update(int date,cal_entry entry);
	string get(int date,int start);
	string get(int date);
	string get_number();
	string get_ith(int i);
};

//Date has to be in mmddyy format
bool check_date(int date);
/*Check the time is in proper format 0000 to 2400
and end time is after start
time format 9 for 0009 is supported
 */
bool check_time(int start,int end);

//Class containing data for all users
class calendar_users{
public:
	map< string , calendar> data_user;
	calendar get_data_user(string username);
	void put_data_user(string username,calendar cal);
	void remove_expired_events();
};

/*Function to interact with the global calendar
@param: input_string is the string the client send
It parses the string and do corresponding changes in the calendar and 
return the corresponding messages whether of success or of any error
*/
string maintain_calendar(string input_string);
