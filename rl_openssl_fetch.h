#ifndef __RL_OPENSSL_H__
#define __RL_OPENSSL_H__

#include <stddef.h>

#define HOST_NAME	"www.wikipedia.org"
//"www.garantibbva.com.tr"
//"www.google.com"
//"www.wikipedia.org"
//"www.youtube.com"
//"www.wikipedia.org"
//"www.wolfssl.com"

//"http://www.wikipedia.org/posts/42"
//"www.youtube.com"
//"www.wikipedia.org"
//"https://common.rediptv.com:443" //"212.224.72.104:80"
//"www.wikipedia.org"
//#define HOST_NAME "https://www.wikipedia.org:443"
#define HOST_PORT "443"
//"80"


#define HOST_RESOURCE "/ "
//"/index.html "
//"/ "
//"/cgi-bin/randbyte?nbytes=32&format=h"

int rl_openssl_fetch(void);


#endif
