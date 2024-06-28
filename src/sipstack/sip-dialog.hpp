#ifndef _SIP_DIALOG_H_
#define _SIP_DIALOG_H_
#include "global-env.hpp"
#include "sip-message.hpp"


class sip_dialog_t {
public:
    /*sip_message_t create_invite();
    sip_message_t create_ack(int code);
    sip_message_t create_cancel();
    sip_message_t create_bye();
    sip_message_t create_notify();
    sip_message_t create_refer();
    sip_message_t create_info();*/
    sip_message_t create_message(const std::string& sip_method); // to protected

    void set_call_id(const std::string& call_id);

protected:
    void make_branch(char* buffer, int buffer_size);

public: 
    std::string m_from_user;
    std::string m_from_domain;
	int m_from_port{ -1 };
    std::string m_from_tag;

	std::string m_to_user;
	std::string m_to_domain;
	int m_to_port{ -1 };
    std::string m_to_tag;

    std::string m_call_id;
    std::string m_via_branch;
	int m_iSeq{ -1 };
	int m_iNextSeq{ -1 };
    std::string m_strContactIp;
	int m_iContactPort{ -1 };
    sip_transport_t m_eTransport;
    /*std::string m_strLocalRtpIp;
    int m_iLocalRtpPort;
    ERtpDirection m_eLocalDirection;
    std::string m_strRemoteRtpIp;
    int m_iRemoteRtpPort;
    ERtpDirection m_eRemoteDirection;
    int m_iCodec;*/

    //CODEC_LIST m_clsCodecList;

    std::string m_strContactUri;
    int m_iRSeq;
    bool m_b100rel;

    /*struct timeval m_sttInviteTime;
    struct timeval m_sttCancelTime;
    struct timeval m_sttStartTime;
    struct timeval m_sttEndTime;*/

    //CSipMessage* m_pclsInvite;
    //SIP_FROM_LIST m_clsRouteList;
    //CSipStack* m_pclsSipStack;
    int m_iSessionVersion;
    bool m_bSendCall;



    /*bool AddSdp(CSipMessage* pclsMessage);

    bool SetLocalRtp(CSipCallRtp* pclsRtp);

    bool SetRemoteRtp(CSipCallRtp* pclsRtp);

    bool SelectLocalRtp(CSipCallRtp* pclsRtp);

    bool SelectRemoteRtp(CSipCallRtp* pclsRtp);

    void GetCdr(CSipCdr* pclsCdr);

    bool IsConnected();

    static bool IsUseCodec(int iCodec);*/

protected:
    //sip_message_t create_message(const char* pszSipMethod);
};


#endif // _SIP_DIALOG_H_
