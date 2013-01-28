#include "calendar.h"
#include <cstdio>
#include <cstdlib>

int check_date(int date){
	short month,day,year;
	year = date % 100;
	date = date / 100;
	month = date % 100;
	date = date /100;
	day = date % 100;

	//if(month <= 12 && )
}

string to_string(int a){
	ostringstream convert;   // stream used for the conversion
	// insert the textual representation of 'Number' in the characters in the stream
	convert << a;      
	return convert.str(); // set 'Result' to the contents of the stream
}

cal_entry::cal_entry(int start,int end,string event){
	if(start > end){
		printf("ERROR start must be before end\n");
		exit(2);
	}
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
bool calendar::add(int date,cal_entry entry){

	list<cal_entry> prev_entry;
	list<cal_entry>::iterator it;
	map<int,list<cal_entry> >::iterator prev_it;

	prev_it = data.find(date);

	//If date is not there, make a new entry in data
	if(prev_it == data.end()){
		data[date].push_back(entry);
	}else{

		prev_entry = data.at(date);

		if(prev_entry.empty()){
			prev_entry.push_back(entry);
			data.at(date) = prev_entry;
			return true;
		}

		//finding the right place to insert the new event
		for (it = prev_entry.begin(); it != prev_entry.end(); it++){

			//if event is before the current entry
			if(entry.end <= (*it).start){
				prev_entry.insert(it,entry);
				data.at(date) = prev_entry;
				return true;
			}
			// if event is after current entry
			else if(entry.start > (*it).end){

				if((*it) == prev_entry.back()){					
					prev_entry.push_back(entry);
					data.at(date) = prev_entry;
					return true;
				}
				else
					continue;
			}
			else
				return false;
		}
	}
	return false;
}


int calendar::remove(int date,int start){
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);
	
	//checking of entry for that date exists
	if(map_it == data.end()){
		return 0;
	}

	list_date = data.at(date);
	for(it=list_date.begin();it != list_date.end();it++){
		if((*it).start == start){
			list_date.erase(it);
			data.at(date) = list_date;
			return 1;
		}
	}
	return 0;

}

int calendar::update(int date,cal_entry entry){
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);
	
	//checking of entry for that date exists
	if(map_it == data.end()){
		return 0;
	}

	list_date = data.at(date);
	for(it=list_date.begin();it != list_date.end();it++){
		if((*it).start == entry.start){
			(*it).end = entry.end;
			(*it).event = entry.event;
			data.at(date) = list_date;
			return 1;
		}
	}
	return 0;
}

string calendar::get(int date,int start){
	string result="";
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;

	map<int,list<cal_entry> >::iterator map_it;

	map_it = data.find(date);
	
	//checking of entry for that date exists
	if(map_it == data.end()){
		return "NO ENTRY FOR "+to_string(date)+"/n";
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

int main(){
	string a;
	cal_entry test1(100,105,"kuch bhi");
	cal_entry test2(110,205,"asdfbhi");
	calendar cal;
	cal.add(91092,test1);
	cal.add(91092,test2);
	cout << cal.get(91092) << endl;
	cout << cal.get(91092,100) << endl;
	cal_entry test3(110,250,"updaetd");
	cal.update(91092,test3);
	cout << cal.get(91092) << endl;
	return 0;
}
