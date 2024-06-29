#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "global-env.hpp"
#include "sip-message.hpp"
#include <WS2tcpip.h>
#include "sip-auth.hpp"
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
"Via: SIP/2.0/UDP 192.168.246.45:53086;branch=z9hG4bKPj90a55fddeb5a445eaa02cf96c998bbc1;received=10.71.6.54;rport=53086\r\n"
"From: <sip:user2@sip.neoprog-iso.kube.itoolabs>;tag=38f007b011fa4084a21db6d32cebde9b\r\n"
"To: <sip:user2@sip.neoprog-iso.kube.itoolabs>;tag=c-bbqtdopzhinr3\r\n"
"Call-ID: 4acbd7cb97074855beb53fef02ee0573\r\n"
"CSeq: 15730 REGISTER\r\n"
"WWW-Authenticate: Digest realm=\"sip.neoprog-iso.kube.itoolabs\", opaque=\"\", qop=\"auth\", algorithm=MD5, nonce=\"UqR-ZknwZ9yrUAYEA4c9MUprgPs\"\r\n"
"Allow: INVITE, ACK, CANCEL, BYE, INFO, REFER, SUBSCRIBE, NOTIFY, REGISTER\r\n"
"Allow-Events: keep-alive\r\n"
"Supported: timer\r\n"
"Server: ITLCS 7.2\r\n"
"Content-Length: 0\r\n"
"\r\n";

std::string local_ip;
SOCKET s;

void send(const char* ip, uint16_t port, const std::string& msg) {
	std::cout << "======================================================" << std::endl;
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
	std::cout << msg << std::endl;
	std::cout << "======================================================" << std::endl;

	sockaddr_in toaddr;
	toaddr.sin_family = AF_INET;
	toaddr.sin_addr.S_un.S_addr = inet_addr("10.71.9.153");
	toaddr.sin_port = htons(5060);
	std::cout << "sendto: " << sendto(s, msg.c_str(), msg.size(), 0, (sockaddr*)&toaddr, sizeof(toaddr)) << std::endl;
}
std::string recv() {
	char buffer[2048] = { 0 };

	sockaddr_in fromaddr;
	int fromlen = sizeof(fromaddr);
	int recv = recvfrom(s, buffer, sizeof(buffer), 0, (sockaddr*)&fromaddr, &fromlen);

	std::string response;
	if (recv >= 0) {
		response = std::string(buffer, recv);
	}
	std::cout << "======================================================" << std::endl;
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
	std::cout << response << std::endl;
	std::cout << "======================================================" << std::endl;
	return response;
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

sip_message_t create_register() {
	sip_message_t reg;
	reg.set_req_uri(sip_uri_t("", "sip.neoprig-iso.kube.itoolabs"));
	reg.set_method("REGISTER");
	reg.set_cseq(1);
	reg.add_via(sip_via_hdr_t(local_ip, 5060, "z9hG4bKPj3af08"));
	reg.set_from(sip_from_hdr_t(sip_uri_t("user2", "sip.neoprog-iso.kube.itoolabs"), "55d27c"));
	reg.set_to(sip_to_hdr_t(sip_uri_t("user2", "sip.neoprog-iso.kube.itoolabs")));
	reg.add_header("Call-ID", "tynweurthcynlrsghsckdg");
	reg.add_header("User-Agent", "Test-UA");
	reg.add_header("Allow", "INVITE");
	return reg;
}

int main() {

	/*sip_message_t msg;
	msg.parse((char*)auth_msg, sizeof(auth_msg));

	std::string v = "Digest realm=\"sip.neoprog-iso.kube.itoolabs\", opaque=\"\", qop=\"auth\", algorithm=MD5, nonce=\"UqR-ZknwZ9yrUAYEA4c9MUprgPs\"";
	sip_credential_hdr_t request;
	//request.parse(v.c_str(), v.size());
	request.m_realm = "biloxi.com";
	request.m_qop = "auth";
	request.m_nonce = "dcd98b7102dd2f0e8b11d0f600bfb0c093";
	request.m_opaque = "5ccc069c403ebaf9f0171e9517f40e41";

	sip_credential_hdr_t response;
	add_auth(request, "INVITE", "bob", "biloxi.com", "zanzibar", &response);

	return 1;*/

	//Authorization: Digest username="user2", 
	//realm="sip.neoprog-iso.kube.itoolabs", 
	//nonce="UqR-ZknwZ9yrUAYEA4c9MUprgPs", 
	//uri="sip:sip.neoprog-iso.kube.itoolabs", 
	//response="1d6eb06004d7a2d8b6b8b62d0a39a446", 
	//algorithm=MD5, 
	//cnonce="62876b404afe4b84a10460cbdfa03b75", 
	//qop=auth, 
	//nc=00000001

	// Initialise winsock
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("Failed. Error Code : %d\r\n", WSAGetLastError());
		return 1;
	}
	printf("Initialised\r\n");

	// Create a socket
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

	local_ip = get_local_ip();
	std::cout << "local_ip: " << local_ip << std::endl;
	


	sip_message_t reg = create_register();
	send("10.71.9.153", 5060, reg.to_string());

	std::string response = recv();

	sip_message_t msg;
	msg.parse(response.c_str(), response.size());

	const sip_credential_hdr_t& challenge = msg.get_auth_hdr();
	sip_credential_hdr_t auth;
	add_auth(challenge, "REGISTER", "user2", "sip.neoprog-iso.kube.itoolabs", "test123", &auth);
	reg.add_header("Authorization", auth.to_string());
	reg.get_to().add_param("tag", msg.get_to().get_param("tag"));

	send("10.71.9.153", 5060, reg.to_string());
	send("10.71.9.153", 5060, reg.to_string());
	send("10.71.9.153", 5060, reg.to_string());

	{
		/*sip_message_t invite;
		invite.set_req_uri(sip_uri_t("702", "sip.neoprig-iso.kube.itoolabs"));
		invite.set_method("REGISTER");
		invite.set_cseq(1);
		invite.add_via(sip_via_hdr_t(local_ip, 5060, "z9hG4bKPj3af08dca64e04cf2a6a224467467b5b2"));
		invite.set_from(sip_from_hdr_t(sip_uri_t("user1", "sip.neoprog-iso.kube.itoolabs"), "55d27c3607a541d3bf0938aa9c5ebfdc"));
		invite.set_to(sip_to_hdr_t(sip_uri_t("702", "sip.neoprog-iso.kube.itoolabs")));
		std::cout << "===========================================" << std::endl;
		std::cout << invite.to_string();
		std::cout << "===========================================" << std::endl;*/


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
