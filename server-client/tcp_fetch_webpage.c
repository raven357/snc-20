/*
use:
	
	./exe www.redline.com.tr 80 GET / "Content-Type: application/x-www-form-urlencoded"
	./exe www.redline.com.tr 80
	./exe www.redline.com.tr 80 GET "/cgi-bin/randbyte?nbytes=32&format=h" "Content-Type: application/x-www-form-urlencoded"
	./exe www.redline.com.tr 80 POST / "name=ARG1&value=ARG2" "Content-Type: application/x-www-form-urlencoded"
*/
//./exe www.redline.com.tr 80 "GET" "/cgi-bin/randbyte?nbytes=32&format=h" " HTTP/1.1\r\n ""\r\nConnection: close\r\n\r\n"
//./exe www.wkipedia.com 80 "GET " "/cgi-bin/randbyte?nbytes=32&format=h" 
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */


//#define host "www.wikipedia.com"
//#define portno "80"

void error(const char *msg) { perror(msg); exit(0); }

void message(int sockfd);


int main(int argc,char *argv[])
{
    int i;

    /* first where are we going to send it? */
    int portno = atoi(argv[2])>0?atoi(argv[2]):80;
    char *host = strlen(argv[1])>0?argv[1]:"localhost";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd;
#if 0	 
	bytes, sent, received, total, message_size;
    char *message, response[4096];

    if (argc < 5) { puts("Parameters: <host> <port> <method> <path> [<data> [<headers>]]"); exit(0); }

    /* How big is the message? */
    message_size=0;
    if(!strcmp(argv[3],"GET"))
    {
        message_size+=strlen("%s %s%s%s HTTP/1.0\r\n");        /* method         */
        message_size+=strlen(argv[3]);                         /* path           */
        message_size+=strlen(argv[4]);                         /* headers        */
        if(argc>5)
            message_size+=strlen(argv[5]);                     /* query string   */
        for(i=6;i<argc;i++)                                    /* headers        */
            message_size+=strlen(argv[i])+strlen("\r\n");
        message_size+=strlen("\r\n");                          /* blank line     */
    }
    else
    {
        message_size+=strlen("%s %s HTTP/1.0\r\n");
        message_size+=strlen(argv[3]);                         /* method         */
        message_size+=strlen(argv[4]);                         /* path           */
        for(i=6;i<argc;i++)                                    /* headers        */
            message_size+=strlen(argv[i])+strlen("\r\n");
        if(argc>5)
            message_size+=strlen("Content-Length: %d\r\n")+10; /* content length */
        message_size+=strlen("\r\n");                          /* blank line     */
        if(argc>5)
            message_size+=strlen(argv[5]);                     /* body           */
    }

    /* allocate space for the message */
    message=malloc(message_size);

    /* fill in the parameters */
    if(!strcmp(argv[3],"GET"))
    {
        if(argc>5)
            sprintf(message,"%s %s%s%s HTTP/1.0\r\n",
                strlen(argv[3])>0?argv[3]:"GET",               /* method         */
                strlen(argv[4])>0?argv[4]:"/",                 /* path           */
                strlen(argv[5])>0?"?":"",                      /* ?              */
                strlen(argv[5])>0?argv[5]:"");                 /* query string   */
        else
            sprintf(message,"%s %s HTTP/1.0\r\n",
                strlen(argv[3])>0?argv[3]:"GET",               /* method         */
                strlen(argv[4])>0?argv[4]:"/");                /* path           */
        for(i=6;i<argc;i++)                                    /* headers        */
            {strcat(message,argv[i]);strcat(message,"\r\n");}
        strcat(message,"\r\n");                                /* blank line     */
    }
    else
    {
        sprintf(message,"%s %s HTTP/1.0\r\n",
            strlen(argv[3])>0?argv[3]:"POST",                  /* method         */
            strlen(argv[4])>0?argv[4]:"/");                    /* path           */
        for(i=6;i<argc;i++)                                    /* headers        */
            {strcat(message,argv[i]);strcat(message,"\r\n");}
        if(argc>5)
            sprintf(message+strlen(message),"Content-Length: %d\r\n",strlen(argv[5]));
        strcat(message,"\r\n");                                /* blank line     */
        if(argc>5)
            strcat(message,argv[5]);                           /* body           */
    }

    /* What are we going to send? */
    printf("Request:\n%s\n",message);
#endif 
	
    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
	
    /* connect the socket */
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
	message(sockfd);
	
    /* send the request */
#if 0
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);

    free(message);
#endif
	close(sockfd);
    return 0;
}
//use:
//./exe www.redline.com.tr 80 GET / "Content-Type: application/x-www-form-urlencoded"

void message(int sockfd)
{
    int  bytes, sent, received, total, message_size;
    char *message, response[4096];

    message_size=0;
 	message_size+=strlen("%s %s HTTP/1.0\r\n");
    message_size+=strlen("GET");  
	message_size+=strlen("/");                     
    message_size+=strlen("Content-Length: %d\r\n")+10;
    message_size+=strlen("\r\n");                          
    message_size+=strlen("Content-Type: application/x-www-form-urlencoded"); 
   	message=malloc(message_size);

    /* fill in the parameters */

	sprintf(message,"%s %s HTTP/1.0\r\n", "GET", "/");                  
	sprintf(message+strlen(message),"Content-Length: %d\r\n",strlen("Content-Type: application/x-www-form-urlencoded"));
	strcat(message,"\r\n");                          
	strcat(message, "Content-Type: application/x-www-form-urlencoded");                      

    /* What are we going to send? */
    printf("Request:\n%s\n",message);

    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
	 //close(sockfd);
    /* process response */
    printf("Response:\n%s\n",response);
	 printf("%d\n",received);

    free(message);

}

