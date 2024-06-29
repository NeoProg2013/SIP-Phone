#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "global-env.hpp"
#include "sip-message.hpp"
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

/*static uint8_t msg[] =
        "INVITE sip:504@4952213312.pbx.zaoit.ru:5060 SIP/2.0\r\n"
        "Via: SIP/2.0/UDP 192.168.100.163:5062;branch=z9hG4bK97979151\r\n"
        "From: \"501\" <sip:v501:password@4952213312.pbx.zaoit.ru;param=value?header=value>;tag=3122704460\r\n"
        "To: <sip:504@4952213312.pbx.zaoit.ru;param=value>;param2=value2\r\n"
        "Call-ID: 1257581178@192.168.100.163\r\n"
        "CSeq: 1 INVITE\r\n"
        "Contact: <sip:v501@192.168.100.163:5062>\r\n"
        "Content-Type: application/sdp\r\n"
        "Allow: INVITE, INFO, PRACK, ACK, BYE, CANCEL, OPTIONS, NOTIFY, REGISTER, SUBSCRIBE, REFER, PUBLISH, UPDATE, MESSAGE\r\n"
        "Max-Forwards: 70\r\n"
	    "P-Asserted-Identity: \"88617308004\" <sip:88617308004@83.239.48.88:5060;user=phone;cpc=ordinary>\r\n"
		"Route: <sip:178.57.113.194:5062;transport=UDP;lr>\r\n"
        "User-Agent: Yealink SIP-T22P 7.73.14.2\r\n"
        "Supported: replaces\r\n"
        "Allow-Events: talk,hold,conference,refer,check-sync\r\n"
        "Content-Length: 312\r\n"
        "\r\n"
        "v=0\r\n"
        "o=- 20001 20001 IN IP4 192.168.100.163\r\n"
        "s=SDP data\r\n"
        "c=IN IP4 192.168.100.163\r\n"
        "t=0 0\r\n"
        "m=audio 11782 RTP/AVP 9 0 8 18 101\r\n"
        "a=rtpmap:9 G722/8000\r\n"
        "a=rtpmap:0 PCMU/8000\r\n"
        "a=rtpmap:8 PCMA/8000\r\n"
        "a=rtpmap:18 G729/8000\r\n"
        "a=fmtp:18 annexb=no\r\n"
        "a=fmtp:101 0-15\r\n"
        "a=rtpmap:101 telephone-event/8000\r\n"
        "a=ptime:20\r\n"
        "a=sendrecv\r\n";*/

static uint8_t msg[] =
"INVITE sip:702@sip.neoprog-iso.kube.itoolabs SIP/2.0\r\n"
"Via: SIP/2.0/UDP 192.168.246.45:50713;rport;branch=z9hG4bKPj3af08dca64e04cf2a6a224467467b5b2\r\n"
"Max-Forwards: 70\r\n"
"From: \"111\" <sip:user1@sip.neoprog-iso.kube.itoolabs>;tag=55d27c3607a541d3bf0938aa9c5ebfdc\r\n"
"To: <sip:702@sip.neoprog-iso.kube.itoolabs>\r\n"
"Contact: \"111\" <sip:user1@192.168.246.45:50713;ob>\r\n"
"Call-ID: 84fd320bbed94402a3e33a47b7eef4a5\r\n"
"CSeq: 2240 INVITE\r\n"
"Allow: PRACK, INVITE, ACK, BYE, CANCEL, UPDATE, INFO, SUBSCRIBE, NOTIFY, REFER, MESSAGE, OPTIONS\r\n"
"Supported: replaces, 100rel, timer, norefersub\r\n"
"Session-Expires: 1800\r\n"
"Min-SE: 90\r\n"
"User-Agent: MicroSIP/3.19.27\r\n"
"Content-Type: application/sdp\r\n"
"Content-Length:   320\r\n"
"\r\n"
"v=0\r\n"
"o=- 3928575244 3928575244 IN IP4 192.168.246.45\r\n"
"s=pjmedia\r\n"
"b=AS:84\r\n"
"t=0 0\r\n"
"a=X-nat:0\r\n"
"m=audio 4000 RTP/AVP 8 101\r\n"
"c=IN IP4 192.168.246.45\r\n"
"b=TIAS:64000\r\n"
"a=rtcp:4001 IN IP4 192.168.246.45\r\n"
"a=sendrecv\r\n"
"a=rtpmap:8 PCMA/8000\r\n"
"a=rtpmap:101 telephone-event/8000\r\n"
"a=fmtp:101 0-16\r\n"
"a=ssrc:82254684 cname:0f5c16a2550a2715\r\n";

static uint8_t auth_msg[] =
"SIP/2.0 401 Authentication Required\r\n"
"Via: SIP/2.0/UDP 192.168.246.45:50713;branch=z9hG4bKPj3af08dca64e04cf2a6a224467467b5b2;rport=5060;received=10.71.6.9\r\n"
"From: \"111\" <sip:user1@sip.neoprog-iso.kube.itoolabs>\r\n"
"To: <sip:702@sip.neoprog-iso.kube.itoolabs>;tag=b-bc1x8jcbi3egg\r\n"
"Call-ID: 84fd320bbed94402a3e33a47b7eef4a5\r\n"
"CSeq: 2240 INVITE\r\n"
"WWW-Authenticate: Digest realm=\"sip.neoprog-iso.kube.itoolabs\", opaque=\"\", qop=\"auth\", algorithm=MD5, nonce=\"mM9_ZtJhCaLD0VE-qQTVs0O4WLQ\"\r\n"
"Allow: INVITE, ACK, CANCEL, BYE, INFO, REFER, SUBSCRIBE, NOTIFY\r\n"
"Allow-Events: keep-alive\r\n"
"Supported: timer\r\n"
"Server: ITLCS 7.2\r\n"
"Content-Length: 0\r\n"
"\r\n";

void send(int s, const char* ip, uint16_t port, const std::string& msg) {
	sockaddr_in toaddr;
	toaddr.sin_family = AF_INET;
	toaddr.sin_addr.S_un.S_addr = inet_addr("10.71.9.153");
	toaddr.sin_port = htons(5060);
	std::cout << "sendto: " << sendto(s, msg.c_str(), msg.size(), 0, (sockaddr*)&toaddr, sizeof(toaddr)) << std::endl;
}
int recv(int s, char* buffer, int buffer_size) {
	sockaddr_in fromaddr;
	int fromlen = sizeof(fromaddr);
	int recv = recvfrom(s, buffer, sizeof(buffer), 0, (sockaddr*)&fromaddr, &fromlen);
	std::cout << buffer << std::endl;
	return recv;
}
std::string get_local_ip() {
	char ac[80];
	if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
		std::cerr << "Error " << WSAGetLastError() <<
			" when getting local host name." << std::endl;
		return "";
	}
	std::cout << "Host name is " << ac << "." << std::endl;

	hostent *phe = gethostbyname(ac);
	if (phe == 0) {
		std::cerr << "Yow! Bad host lookup." << std::endl;
		return "";
	}
	in_addr addr;
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	std::string source_ip = inet_ntoa(addr);
	return source_ip;
}
void resolve() {
	/*addrinfo* res = nullptr;
	getaddrinfo("google.com", "", 0, &res);

	for (addrinfo* i = res; i != NULL; i = i->ai_next) {
		char str[INET6_ADDRSTRLEN];
		if (i->ai_addr->sa_family == AF_INET) {
			struct sockaddr_in *p = (struct sockaddr_in *)i->ai_addr;
			printf("%s\n", inet_ntop(AF_INET, &p->sin_addr, str, sizeof(str)));
		}
		else if (i->ai_addr->sa_family == AF_INET6) {
			struct sockaddr_in6 *p = (struct sockaddr_in6 *)i->ai_addr;
			printf("%s\n", inet_ntop(AF_INET6, &p->sin6_addr, str, sizeof(str)));
		}
	}*/
}

int main() {

	// Initialise winsock
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code : %d\r\n", WSAGetLastError());
		return 1;
	}
	printf("Initialised\r\n");

	// Create a socket
	SOCKET s;
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d\r\n", WSAGetLastError());
	}
	printf("Socket created\r\n");

	// Prepare the sockaddr_in structure
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5060);
	if (bind(s, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code : %d\r\n", WSAGetLastError());
		return 1;
	}
	printf("Bind done\r\n");

	std::string local_ip = get_local_ip();
	std::cout << "local_ip: " << local_ip << std::endl;
	


	



	{
		sip_message_t invite;
		invite.set_req_uri(sip_uri_t("702", "sip.neoprig-iso.kube.itoolabs"));
		invite.set_method("INVITE");
		invite.set_cseq(1);
		invite.add_via(sip_via_hdr_t(local_ip, 5060, "z9hG4bKPj3af08dca64e04cf2a6a224467467b5b2"));
		invite.set_from(sip_from_hdr_t(sip_uri_t("user1", "sip.neoprog-iso.kube.itoolabs"), "55d27c3607a541d3bf0938aa9c5ebfdc"));
		invite.set_to(sip_to_hdr_t(sip_uri_t("702", "sip.neoprog-iso.kube.itoolabs")));
		std::cout << "===========================================" << std::endl;
		std::cout << invite.to_string();
		std::cout << "===========================================" << std::endl;


		//invite.mutable_to_hdr().set_uri(sip_uri_t("702", "sip.neoprog-iso.kube.itoolabs"));

		/*sip_message.parse((const char*)msg, sizeof(msg));
		std::cout << "===========================================" << std::endl;
		std::string invite = sip_message.to_string();
		std::cout << invite;
		std::cout << "===========================================" << std::endl;

		{
			sip_message_t auth;
			auth.parse((const char*)auth_msg, sizeof(auth_msg));
			std::cout << "===========================================" << std::endl;
			std::cout << auth.to_string();
			std::cout << "===========================================" << std::endl;
		}*/


	}

	/*{
		sip_dialog_t d;
        d.m_from_user = "user1";
		d.m_from_domain = "sip.neoprog-iso.kube.itoolabs";
		d.m_from_port = 0;
		d.m_from_tag = "12345";

		d.m_from_user = "user2";
		d.m_from_domain = "sip.neoprog-iso.kube.itoolabs";
		d.m_from_port = 0;
		d.m_from_tag = "";

		d.m_call_id = "gkjdvnhvycjmghvdghzfigvhdflgjhsdg";
		d.m_via_branch = "z9hG4bKtttt";
		d.m_iSeq = 1;
		d.m_strContactIp = "127.0.0.1";
		d.m_iContactPort = 5060;
		sip_message_t m = d.create_message("INVITE");
		m.print();
	}*/

	return 0;
}
