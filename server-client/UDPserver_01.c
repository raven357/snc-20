#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <arpa/inet.h> //the arpa/inet.h header shall define the in_addr structure etc. described in netinet/in.h
/* Inclusion of the <netinet/in.h> header may also make visible all symbols from <arpa/inet.h>. */
#include <netinet/in.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#define BUF_MAXSIZE     4096

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in srv_addr;
    struct sockaddr_in cli_addr;
    char buf[BUF_MAXSIZE];
    int portno;
    socklen_t addr_len, opt_len;
    short numbyt;
            
    if(argc != 2){
        fprintf(stderr, "Usege: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        perror("ERROR socket()");
        exit(EXIT_FAILURE); 
    }           
    else
        printf("socket(): SUCCESSFUL\n");
    
    portno = atoi(argv[1]);
 
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(portno);
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(srv_addr.sin_zero, 0, 8);
     
    if(bind(sockfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) < 0) {
        perror("ERROR: bind()\n");
        printf("Errno value: %s\n", strerror(errno));
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    else
        printf("bind(): SUCCESSFUL\n");

    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0; 
    opt_len = sizeof(timeout);

    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (void *)&timeout, opt_len) < 0){
        perror("ERROR: setsockopt()\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    addr_len = sizeof(cli_addr);
       
        while(1){
           if((numbyt = recvfrom(sockfd, buf, BUF_MAXSIZE, 0, (struct sockaddr *)&cli_addr, &addr_len)) < 0){
                    if(errno == EWOULDBLOCK || errno == EAGAIN){
                        printf("ERROR: %s\n", errno == EWOULDBLOCK ? "EWOULDBLOCK" : "EAGAIN");
                        continue;                                  
                    }
                    else {
                        perror("ERROR: recvfrom()\n");
                        close(sockfd);
                        exit(EXIT_FAILURE);
                    }                                  
            }       
            else
                printf("%i: %s\n", numbyt, buf);  
  
           if(sendto(sockfd, buf, numbyt, 0, (struct sockaddr*)&cli_addr, sizeof(cli_addr)) != numbyt) {
                perror("ERROR: sendto()\n");
                close(sockfd);
                exit(EXIT_FAILURE);
             }                
    
        }        
	         
	return 0;	
}

