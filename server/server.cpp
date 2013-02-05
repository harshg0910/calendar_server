#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "calendar.h"

using namespace std;


//Global calnedar_user
calendar_users cal_user;


void error(const char *msg)
{
	perror(msg);
	exit(1);
}

string maintain_calendar(char* input_string){
	vector<string> input;
	char* token = strtok(input_string, " ");
	do{	
		if(token != NULL)
			input.push_back(token);
	}	
	while(token=strtok(NULL," "));

	if(input.size() < 3 || input.size() > 6)
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
	else return "ERROR : Unknow function\n";
	//updating the data
	cal_user.put_data_user(user,cal);


}

//TODO Check for correct date in calendar.cpp

int main(int argc, char *argv[])
{


	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	while(1){
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, 
				(struct sockaddr *) &cli_addr, 
				&clilen);
		if (newsockfd < 0) 
			error("ERROR on accept");
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");

		string to_send = maintain_calendar(buffer) ;

		n = write(newsockfd,to_send.c_str(),to_send.size());
		if (n < 0) error("ERROR writing to socket");

		close(newsockfd);
	}
	close(sockfd);
	return 0; 
}
