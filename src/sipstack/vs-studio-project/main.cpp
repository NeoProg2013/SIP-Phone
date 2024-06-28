#include "global-env.hpp"
#include "sip-message.hpp"
#pragma comment (lib, "ws2_32.lib")

static uint8_t msg[] =
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
        "a=sendrecv\r\n";

int main() {

	//504@4952213312.pbx.zaoit.ru:5060
    //sip_uri_t uri("504", "4952213312.pbx.zaoit.ru", 5060);
    //std::cout << uri.to_string() << std::endl;

	{
		sip_message_t sip_message;
		sip_message.parse((const char*)msg, sizeof(msg));
		std::cout << "===========================================" << std::endl;
		std::cout << sip_message.to_string() << std::endl;
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
