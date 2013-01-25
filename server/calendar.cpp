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
	if(event.compare(NULL) == 0){
		printf("ERROR event cannot be NULL\n");
		exit(2);
	}	
	if(start > end){
		printf("ERROR start must be before end\n");
		exit(2);
	}
	this->start = start;
	this->end = end;
	this->event = event;
}


bool calendar::add(int date,cal_entry entry){

	list<cal_entry> prev_entry;
	list<cal_entry>::iterator it;
	prev_entry = data.at(date);

		printf("In  add\n");
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
			if(it == prev_entry.end()){
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

int calendar::remove(int date,int start){

}

int calendar::update(int date,cal_entry entry){

}

string calendar::get(int date,int start){

}

string calendar::get(int date){
	string result;

		printf("In  get\n");
	list<cal_entry> list_date;
	list<cal_entry>::iterator it;
	
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


}

int main(){
	string a;
	cal_entry test(100,105,"kuch bhi");
	calendar cal;
	cal.add(91092,test);
	cal.get(91092);
	return 0;
}
