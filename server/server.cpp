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

#define BUFFER_LEN 1000

void error(const char *msg)
{
	perror(msg);
	exit(1);
}
//TODO Check for correct date in calendar.cpp

int main(int argc, char *argv[])
{


	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[BUFFER_LEN];
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
		bzero(buffer,BUFFER_LEN	);
		n = read(newsockfd,buffer,BUFFER_LEN);
		if (n < 0) error("ERROR reading from socket");
		
		string to_send="";
		vector<string> input_data;
		char* token = strtok(buffer,"\n");

		//We cannot parse nesting in strtok
		do{
			input_data.push_back(token);
		}while( (token = strtok(NULL,"\n")) );
		
		for (unsigned int i=0;i<input_data.size();i++){	
			to_send += maintain_calendar(input_data[i]) + "\n";
		}
		n = write(newsockfd,to_send.c_str(),to_send.size());
		if (n < 0) error("ERROR writing to socket");

		close(newsockfd);
	}
	close(sockfd);
	return 0; 
}
