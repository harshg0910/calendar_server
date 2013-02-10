#include "calendar.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>

//Global calnedar_user
calendar_users cal_user;


int check_date(int date){
/*	short month,day,year;
	year = date % 100;
	date = date / 100;
	month = date % 100;
	date = date /100;
	day = date % 100;
*/
	//if(month <= 12 && )
	return 0;
}

string to_string(int a){
	ostringstream convert;   // stream used for the conversion
	// insert the textual representation of 'Number' in the characters in the stream
	convert << a;      
	return convert.str(); // set 'Result' to the contents of the stream
}

cal_entry::cal_entry(int start,int end,string event){
	this->start = start;
	this->end = end;
	this->event = event;

}

bool cal_entry::operator==(cal_entry other){
	if(other.start == start && other.end == end &&
			other.event == event)
		return true;
	else
		return false;
}
string calendar::add(int date,cal_entry entry){

	list<cal_entry> prev_entry;
	list<cal_entry>::iterator it;
	map<int,list<cal_entry> >::iterator prev_it;

	prev_it = data.find(date);

	//If date is not there, make a new entry in data
	if(prev_it == data.end()){
		data[date].push_back(entry);
		return "Added Successfully\n"; 
	}else{

		prev_entry = data.at(date);

		if(prev_entry.empty()){
			prev_entry.push_back(entry);
			data.at(date) = prev_entry;
			return "Added Successfully\n";
		}

		//finding the right place to insert the new event
		for (it = prev_entry.begin(); it != prev_entry.end(); it++){

			//if event is before the current entry
			if(entry.end <= (*it).start){
				prev_entry.insert(it,entry);
				data.at(date) = prev_entry;
				return "Added Successfully\n";
			}
			// if event is after current entry
			else if(entry.start > (*it).end){

				if((*it) == prev_entry.back()){					
					prev_entry.push_back(entry);
					data.at(date) = prev_entry;
					return "Added Successfully\n";
				}
				else
					continue;
			}
			else
				return "ERROR : Conflict detected\n";
		}
	}
	return "ERROR : Somthing unknown error happend\n";
}


string calendar::remove(int date,int start){
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);
	
	//checking of entry for that date exists
	if(map_it == data.end()){
		return "ERROR : No such date entry exists\n";
	}

	list_date = data.at(date);
	for(it=list_date.begin();it != list_date.end();it++){
		if((*it).start == start){
			list_date.erase(it);
			data.at(date) = list_date;
			return "Successfully Removed\n";
		}
	}
	return "ERROR : No event for this start time\n";

}

string calendar::update(int date,cal_entry entry){
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);
	
	//checking of entry for that date exists
	if(map_it == data.end()){
		return "ERROR : No such entry exists\n";
	}

	list_date = data.at(date);
	for(it=list_date.begin();it != list_date.end();it++){
		if((*it).start == entry.start){
			(*it).end = entry.end;
			(*it).event = entry.event;
			data.at(date) = list_date;
			return "Successfully Updated\n";
		}
	}
	return "ERROR : Unknow error happened\n";
}

string calendar::get(int date,int start){
	string result="";
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);
	
	//checking of entry for that date exists
	if(map_it == data.end()){
		return "NO ENTRY FOR "+to_string(date)+"\n";
	}

	list_date = data.at(date);

	result += to_string(date);
	result += "\n";
	for(it=list_date.begin();it != list_date.end();it++){
		//If relevent value is found 
		if((*it).start == start){
			result += "\tStart:";
			result += to_string((*it).start);
			result += " End:";
			result += to_string((*it).end);
			result += " Event:";
			result += (*it).event;
			result += "\n";
			return result;
		}
	}

	return "Entry not exist\n";
}


string calendar::get(int date){
	string result="";
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);

	if(map_it == data.end()){
		return "NO ENTRY FOR "+to_string(date)+"/n";
	}

	list_date = data.at(date);

	result += to_string(date);
	result += "\n";
	for(it=list_date.begin();it != list_date.end();it++){
		result += "\tStart:";
		result += to_string((*it).start);
		result += " End:";
		result += to_string((*it).end);
		result += " Event:";
		result += (*it).event;
		result += "\n";
	}

	return result;
}

string calendar::get_number(){
	int number = 0;
	map<int,list<cal_entry> >::iterator map_it;

	for(map_it = data.begin();map_it != data.end();map_it++){
		number += (map_it->second).size() ;
	}
	return to_string(number);
}

string calendar::get_ith(int i){
	string result="";
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	if(i > atoi(get_number().c_str()))
		return "Not enough entry in calendar\n";
	
	for(map_it = data.begin();map_it != data.end();map_it++){
		
		//If i is in the current date
		if(i <= (int)(map_it->second).size()){
			list_date = (map_it->second);
			result += to_string(map_it->first);
			result += "\n";
			int index = 0;
				for(it=list_date.begin();it != list_date.end() && index <= i ;it++,index++){
					if(index == i-1){
					result += "\tStart:";
					result += to_string((*it).start);
					result += " End:";
					result += to_string((*it).end);
					result += " Event:";
					result += (*it).event;
					result += "\n";
					cout << i <<'\t'<< index << endl ;
					}

				}

		}else{
			//The required entry is in another date
			i -= (map_it->second).size();
		}	
	}

	return result;

}

calendar calendar_users::get_data_user(string username){

	calendar a;
	map<string,calendar>::iterator c = data_user.find(username);
	if(c != data_user.end())
		return data_user.at(username);
	else
		data_user[username] = a;
	return data_user[username];
}

void calendar_users::put_data_user(string username,calendar cal){
	data_user[username] = cal;
}
/*
   int main(){

   calendar_users cal_user;
   string a;
   cal_entry test1(100,105,"kuch bhi");
   cal_entry test2(110,205,"asdfbhi");
   calendar cal;
   cal.add(91092,test1);
   cal.add(91092,test2);

   cal_user.put_data_user("harsh",cal);

   calendar c =cal_user.get_data_user("harsh");

   cout << c.get(91092) << endl;
   cout << c.get(91092,100) << endl;
   cal_entry test3(110,250,"updaetd");
   c.update(91092,test3);
   cal_user.put_data_user("harsh",c);
   cout << cal_user.get_data_user("harsh").get(91092) << endl;
 */
string maintain_calendar(string input_string){
	vector<string> input;
	char buff[300];
	strcpy(buff,input_string.c_str());
	char* token = strtok(buff, " ");
	do{	
		if(token != NULL)
			input.push_back(token);
	}
	while( (token=strtok(NULL," ")) );
	if(input.size() < 2 || input.size() > 6)
		return "ERROR : Improper number of Arguments\n";

	string user = input[0];
	//Getting calendar corresponding to user

	calendar cal = cal_user.get_data_user(user);

	string func = input[1];
	if(func == "add"){
		if(input.size() != 6)
			return "ERROR : Improper number of arguments for add\n";
		int date = atoi(input[2].c_str());
		int start = atoi(input[3].c_str());
		int end = atoi(input[4].c_str());
		if(date<=0 || start<=0 || end<=0)
			return "ERROR : Date,start and end time must be positive integers\n";
		if(start > end )
			return "ERROR : Start must be before end\n";
		string event = input[5];

		cal_entry entry(start,end,event);
		string result = cal.add(date,entry);
		if(result == "Added Successfully\n")
			cal_user.put_data_user(user,cal);
		return result;


	}
	else if(func=="remove"){
		if(input.size() != 4)
			return "ERROR : Improper arguments for remove\n";
		int date = atoi(input[2].c_str());
		int start = atoi(input[3].c_str());
		if(date<=0 || start<=0)
			return "ERROR : Date and start time must be positive integers\n";
		string result = cal.remove(date,start);
		if(result == "Successfully Removed\n")
			cal_user.put_data_user(user,cal);
		return result;

	}
	else if(func=="update"){
		if(input.size() != 6)
			return "ERROR : Improper number of arguments for update\n";
		int date = atoi(input[2].c_str());
		int start = atoi(input[3].c_str());
		int end = atoi(input[4].c_str());
		if(date<=0 || start<=0 || end<=0)
			return "ERROR : Date,start and end time must be positive integers\n";
		if(start > end )
			return "ERROR : Start must be before end\n";
		string event = input[5];

		cal_entry entry(start,end,event);
		string result = cal.update(date,entry);
		if(result == "Successfully Updated\n")
			cal_user.put_data_user(user,cal);
		return result;

	}
	else if(func=="get"){
		if(input.size() == 4){
			int date = atoi(input[2].c_str());
			int start = atoi(input[3].c_str());
			if(date<=0 || start<=0)
				return "ERROR : Date and start time must be positive integers\n";
			return cal.get(date,start);


		}
		else if(input.size() == 3){
			int date = atoi(input[2].c_str());
			if(date<=0)
				return "ERROR : Date must be positive integers\n";
			return cal.get(date);


		}
		else
			return "ERROR : Improper argunments for get\n";

	}
	else if(func=="get_number"){
		if(input.size() == 2){
			return cal.get_number();	
		}else
			return "ERROR : Improper Arguments\n";
	}
	else if(func=="get_ith"){
		if(input.size() == 3){
			int i = atoi(input[2].c_str());
			return cal.get_ith(i);
		}
	}
	return "ERROR : Unknow function\n";

}
