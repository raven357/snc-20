#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>

#define BUF_MAXSIZE	4096

int main(int argc, char *argv[])
{
	int sockfd;
	char buf[BUF_MAXSIZE];
	char *hostname;
	int portno;
	struct sockaddr_in srv_addr;
	struct hostent *server;
	socklen_t addr_len;
	short numbyt;
	int n;

	if(argc != 3){
		fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
		exit(EXIT_FAILURE); 
	}
	
	hostname = argv[1];
	portno = atoi(argv[2]);
		
	if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
		perror("ERROR: socket()\n");
		exit(EXIT_FAILURE);
	}
	else 
		printf("socket(): SUCCESSFUL\n");
	
	if((server = gethostbyname(hostname)) == NULL){
		fprintf(stderr, "ERROR no such host as %s\n", hostname);
		exit(EXIT_FAILURE);
	}	
	
	memset((char *)&srv_addr, '\0', sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	memmove((char *)server->h_addr, (char *)&srv_addr.sin_addr.s_addr, server->h_length);
	srv_addr.sin_port =	htons(portno);

	addr_len = sizeof(srv_addr);
	while(1){
		printf("please enter message:\n");
		fgets(buf, BUF_MAXSIZE, stdin);		
		if((numbyt = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&srv_addr, addr_len)) < 0){
			perror("ERROR: sendto()\n");
			close(sockfd);
			exit(EXIT_FAILURE);
		}		
		
		memset((void *)buf, '\0', sizeof(buf));
		if((numbyt = recvfrom(sockfd, buf, BUF_MAXSIZE, 0, (struct sockaddr *)&srv_addr, &addr_len)) < 0){
			perror("ERROR: recvfrom()\n");
			close(sockfd);
			exit(EXIT_FAILURE);		
		}

		printf("%s", buf);
		fflush(stdout);
	}
	return 0;	
}
