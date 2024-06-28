#include "global-env.hpp"
#include "sipstack.hpp"


//
// public virtual API and ctors
sipstack_t::sipstack_t() {

}
sipstack_t::~sipstack_t() {
#if defined(_MSC_VER)
	closesocket(global_env::SIP_SOCKET);
#else
	close(global_env::SIP_SOCKET);
#endif
}

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
bool sipstack_t::init() {
#if defined(_MSC_VER)
	global_env::SIP_SOCKET = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = INADDR_ANY;
	sa.sin_port = htons(global_env::SIP_PORT);
	std::cout << "bind: " << bind(global_env::SIP_SOCKET, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) << std::endl;
#else
	if (socket(global_env::SIP_SOCKET, Sn_MR_UDP, global_env::SIP_PORT, 0x00) < 0) {
		return false;
	}
#endif
	return true;
}
void sipstack_t::tick() {
	uint8_t buffer[1024] = { 0 };
	uint8_t addr[4] = { 0 };
	uint16_t port = 0;

#if defined(_MSC_VER)
	sockaddr_in from;
	int from_length = sizeof(from);
	int length = recvfrom(global_env::SIP_SOCKET, reinterpret_cast<char*>(buffer), 1024, 0, reinterpret_cast<sockaddr*>(&from), &from_length);
	memcpy(addr, &from.sin_addr.S_un.S_addr, sizeof(addr));
	port = ntohs(from.sin_port);
#else
	int length = recvfrom(global_env::SIP_SOCKET, buffer, 1024, addr, &port);
#endif

	if (length > 0) {
		sip_message_t sip_message;
		sip_message.parse((const char*)buffer, length);
		;
	}
	;
}

//
// protected API. Only non-virtual methods

//
// public static API. Only static methods

//
// protected static API. Only static methods
