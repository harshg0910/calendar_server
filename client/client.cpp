#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctime>
#include <iostream>
#include <sstream>
using namespace std;
#define BUFFER_LEN 256

void error(const char *msg)
{
	perror(msg);
	exit(1);
}


string to_string(int a){
	ostringstream convert;   // stream used for the conversion
	// insert the textual representation of 'Number' in the characters in the stream
	convert << a;      
	return convert.str(); // set 'Result' to the contents of the stream
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[255];
	if (argc < 5) {
		cout << "Adding an event: ./mycal hostname port myname add 031505 0800 0900 Exam\n";
		cout << "Removing an event: ./mycal hostname port myname remove 031505 0800\n";
		cout << "Updating an event: ./mycal hostname port myname update 031505 0800 1000 OralExam\n";
		cout << "Getting an event 1: ./mycal hostname port myname get 031505 0800\n";
		cout << "Getting an event 2: ./mycal hostname port myname get 031505\n";
		cout << "Getting All events : ./mycal hostname port myname getall\n";
		exit(2);

	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR in connecting");

	if(!strcmp(argv[4],"getall")){
		bzero(buffer,BUFFER_LEN);
		strcat(buffer,argv[3]);
		strcat(buffer," get_number");
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			error("ERROR writing to socket");
		bzero(buffer,BUFFER_LEN);
		n = read(sockfd,buffer,BUFFER_LEN);
		if (n < 0) 
			error("ERROR reading from socket");
		int number = atoi(buffer);
		for(int i=1;i<=number;i++){
			sleep(2);
			bzero(buffer,BUFFER_LEN);
			strcat(buffer,argv[3]);
			strcat(buffer," get_ith ");
			strcat(buffer,to_string(i).c_str());
			
			n = write(sockfd,buffer,strlen(buffer));
			if (n < 0) 
				error("ERROR writing to socket");

			bzero(buffer,BUFFER_LEN);
			n = read(sockfd,buffer,BUFFER_LEN);
			if (n < 0) 
				error("ERROR reading from socket");
			printf("%s",buffer);

		}

	}else{	
		for(int i=3;i<argc;i++){
			strcat(buffer,argv[i]);
			strcat(buffer," ");
		}
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			error("ERROR writing to socket");

		bzero(buffer,BUFFER_LEN);
		n = read(sockfd,buffer,BUFFER_LEN);
		if (n < 0) 
			error("ERROR reading from socket");
		printf("%s",buffer);

	}

	/*
	   for(int k=0;k<100;k++){
	   sleep(1);
//strcpy(buffer,"harsh1 add 1234 1234 2345 t1");
cin.getline(buffer,255);
printf("%s\n",buffer);
n = write(sockfd,buffer,strlen(buffer));
if (n < 0) 
error("ERROR writing to socket");

bzero(buffer,256);
n = read(sockfd,buffer,255);
if (n < 0) 
error("ERROR reading from socket");
printf("%s",buffer);
}*/
close(sockfd);
return 0;
}
