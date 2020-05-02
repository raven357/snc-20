#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
char* gethostname(char *host);

int main(){
	
  
	printf("Hello %s\n", gethostname("www.wikipedia.org"));
}

char* gethostname(char *hostname)
{
//"www.usna.edu";  //the hostname we are looking up

  struct addrinfo *result;    //to store results
  struct addrinfo hints;      //to indicate information we want

  struct sockaddr_in *saddr;  //to reference address

  int s; //for error checking

  memset(&hints,0,sizeof(struct addrinfo));  //zero out hints
  hints.ai_family = AF_INET; //we only want IPv4 addresses

  //Convert the hostname to an address
  if( (s = getaddrinfo(hostname, NULL, &hints, &result)) != 0){
    fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(s));
    exit(1);
  }

  //convert generic socket address to inet socket address
  saddr = (struct sockaddr_in *) result->ai_addr;
	
	//printf("Hello %s\n", gethost);
  //print the address
  

  //free the addrinfo struct
  freeaddrinfo(result);
	return inet_ntoa(saddr->sin_addr);
}
