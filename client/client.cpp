#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctime>
using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[255];
	/*if (argc < 6) {
		printf("Adding an event: ./mycal hostname port myname add 031505 0800 0900 Exam\nRemoving an event: ./mycal hostname port myname remove 031505 0800\nUpdating an event: ./mycal hostname port myname update 031505 0800 1000 OralExam\nGetting an event 1: ./mycal hostname port myname get 031505 0800\nGetting an event 2: ./mycal hostname port myname get 031505\n");
		exit(2);

	}*/

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
	
	/*
	for(int i=3;i<argc;i++){
		strcat(buffer,argv[i]);
		strcat(buffer," ");
		}*/
	while(1){
		sleep(1);
		strcpy(buffer,"harsh add 1234 1234 2345 t1");
		printf("%s\n",buffer);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			error("ERROR writing to socket");

		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) 
			error("ERROR reading from socket");
		printf("%s\n",buffer);
	}
	close(sockfd);
	return 0;
}
