#include <cyassl/openssl/ssl.h>
#include <cyassl/openssl/err.h>
#include <cyassl/openssl/opensslconf.h>

#include "rl_ssl_fetch_webpage.h"

static void init_openssl(void);
static void error_msg(unsigned long err, const char* msg);
static int conn_socket(void);

int rl_ssl_fetch_webpage(void)
{	
	long res = 1;
    int ret = 1;
    unsigned long ssl_err = 0;
	int sockfd = 0;
    SSL *ssl = NULL;
    SSL_CTX* ctx = NULL;

	
	init_openssl();

	do{	
		const SSL_METHOD* method = TLSv1_2_client_method();

        ssl_err = ERR_get_error();        
        if(method == NULL){
            error_msg(ssl_err, "SSLv23_client_method");
            break; 
        }

        ctx = SSL_CTX_new(method);
        ssl_err = ERR_get_error();
        if(ctx == NULL){
           error_msg(ssl_err, "SSL_CTX_new");
           break;
        }
        
		ssl = SSL_new(ctx);
		ssl_err = ERR_get_error();
		if(ssl == NULL){
			error_msg(ssl_err, "SSL_new");
			break;
		}
	
		sockfd = conn_socket();
	
		res = SSL_set_fd(ssl, sockfd);
		ssl_err = ERR_get_error();
		if(res != 1){
			error_msg(ssl_err, "SSL_set_fd");
			break;
		}
		
		SSL_set_verify(ssl, SSL_VERIFY_NONE, NULL);

		res = SSL_connect(ssl);
		ssl_err = ERR_get_error();
		if(res != 1){
			error_msg(ssl_err, "SSL_connect");
			break;
		}
		
		int total, sent, received, bytes;
		char response[256] = {};
		char message[256];
		snprintf(message, sizeof(message), "GET " HOST_RESOURCE "HTTP/1.1\r\nHost: " HOST_NAME "\r\nConnection: close\r\n\r\n");
		
		/* sent the request */
		printf("Request:\n%s\n", message);

		total = strlen(message);
   	 	sent = 0;
		do {
			bytes = SSL_write(ssl,message+sent,total-sent);
			ssl_err = ERR_get_error();
        	if (bytes == 0)
            	break;
			else if (bytes < 0){
           		error_msg(ssl_err, "SSL_write");
				exit(EXIT_FAILURE);
			}        	
 			sent += bytes;
    	} while (sent < total);

		printf("Sent total %d bytes\n", total);

    	/* receive the response */
		printf("\nResponse: \n");
    	memset(response,0,sizeof(response));
    	total = 0;
    	received = 0;
    	do {
        	bytes = SSL_read(ssl,response, sizeof(response) - 1);
			ssl_err = ERR_get_error();
			if(bytes > 0)
				response[bytes] = '\0';
			printf("%s", response);
			if(bytes == 0)
            	break;        	
			else if (bytes < 0){
            	error_msg(ssl_err, "SSL_read");
				exit(EXIT_FAILURE);
			}
			received = bytes;
			total += received;
    	} while (received > 0);
		
		printf("\nRecieved total %d bytes\n", total);

    	ret = 0;  
  
    } while (0);
	
	if(ret == 0)
    printf("DONE\n");
		
    if(ctx != NULL)
        SSL_CTX_free(ctx);

	if(ssl != NULL);
		SSL_free(ssl);

	close(sockfd);		
	printf("Close socket\n");

    return ret;
}

static void init_openssl(void)
{
    (void)SSL_library_init();
    /* Cannot fail (always returns success) */
    	
    SSL_load_error_strings();
    /* Cannot fail */
    /* SSL_load_error_strings loads both libssl and libcrypto strings */
    
    /* Include <openssl/opensslconf.h> to get this define */
#if defined (OPENSSL_THREADS)
    fprintf(stdout, "Thread support enabled...\n");
#else 
	fprintf(stdout, "No thread support...\n");
#endif
}

static void error_msg(unsigned long err, const char* msg)
{
	const char* str = ERR_reason_error_string(err);
	
	if(str)
		printf("%s\n", str); 
	else 
		printf("%s failed %lu\n", msg, err);	
}

static int conn_socket(void)
{
	int res, sockfd;
	struct addrinfo hints = {}, *srvaddrs; 
       		
	memset(&hints, 0, sizeof(hints));	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if((res = getaddrinfo(HOST_NAME, HOST_PORT, &hints, &srvaddrs)) != 0){
		perror("ERROR: getaddrinfo()\n");
		exit(EXIT_FAILURE);
	}

	if((sockfd = socket(srvaddrs->ai_family, srvaddrs->ai_socktype, srvaddrs->ai_protocol)) < 0){
		perror("ERROR: socket()\n");
		exit(EXIT_FAILURE);
	}
	
	struct timeval timeout;
    timeout.tv_sec = 1; //seconds 
    timeout.tv_usec = 0; //microseconds
    socklen_t opt_len = sizeof(timeout);

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (void *) &timeout, opt_len);

	if(connect(sockfd, srvaddrs->ai_addr, srvaddrs->ai_addrlen) != 0){
		close(sockfd);		
		perror("ERROR: connect()\n");
		exit(EXIT_FAILURE);
	}
		
	freeaddrinfo(srvaddrs);	
	
	return sockfd;	
}

