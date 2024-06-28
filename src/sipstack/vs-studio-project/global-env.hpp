#ifndef _GLOBAL_ENV_H_
#define _GLOBAL_ENV_H_
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <cctype>
#include <functional>

#if defined(_MSC_VER)
#include <winsock2.h>
#endif


#if defined(_MSC_VER)
namespace global_env {
	static int DHCP_SOCKET = -1; // Changed by socket() call
	static int SIP_SOCKET  = -1; // Changed by socket() call
	static const uint16_t SIP_PORT = 5060;
}
#else
namespace global_env {
	static const int DHCP_SOCKET = 1;
	static const int SIP_SOCKET = 2;
	static const uint16_t SIP_PORT = 5060;
}
#endif
namespace global_env {
	int strcasecmp(const char* s1, const char* s2);
}


#endif // _GLOBAL_ENV_H_