#ifndef __RL_OPENSSL_H__
#define __RL_OPENSSL_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define HOST_NAME "www.google.com"
//"www.google.com"
//"www.wikipedia.org"
#define HOST_PORT "443"
#define HOST_RESOURCE "/ "
//"/ "
//"/index.html "

int rl_ssl_fetch_webpage(void);

#endif
