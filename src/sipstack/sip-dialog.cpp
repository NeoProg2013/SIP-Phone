#include "global-env.hpp"
#include "sip-dialog.hpp"


//
// public virtual API. Only virtual methods and ctors

//
// protected virtual API. Only virtual methods and ctors

//
// public API. Only non-virtual methods
void set_call_id(const std::string& call_id) {

}
/*sip_message_t sip_dialog_t::create_invite() {
    sip_message_t sip_message = this->create_message(SIP_METHOD_INVITE);

    char branch[SIP_BRANCH_MAX_SIZE];

    SipMakeBranch(szBranch, sizeof(szBranch));

    pclsMessage->AddVia(m_pclsSipStack->m_clsSetup.m_strLocalIp.c_str(),
                        m_pclsSipStack->m_clsSetup.GetLocalPort(m_eTransport), szBranch, m_eTransport);
    m_strViaBranch = szBranch;

    //if (m_b100rel) {
    //    sip_message.add_header("Allow", "PRACK, INVITE, ACK, BYE, CANCEL, REFER, NOTIFY, MESSAGE");
    //    sip_message.add_header("Supported", "100rel");
    //    sip_message.add_header("Require", "100rel");
    //}

    AddSdp(pclsMessage);

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreateAck(int iStatusCode) {
    sip_message_t* pclsMessage = create_message(SIP_METHOD_ACK);
    if (pclsMessage == NULL) return NULL;

    if (iStatusCode / 100 != 2) {
        pclsMessage->AddVia(m_pclsSipStack->m_clsSetup.m_strLocalIp.c_str(),
                            m_pclsSipStack->m_clsSetup.GetLocalPort(m_eTransport), m_strViaBranch.c_str(),
                            m_eTransport);
    }

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreateCancel() {
    sip_message_t* pclsMessage = create_message(SIP_METHOD_CANCEL);
    if (pclsMessage == NULL) return NULL;

    pclsMessage->AddVia(m_pclsSipStack->m_clsSetup.m_strLocalIp.c_str(),
                        m_pclsSipStack->m_clsSetup.GetLocalPort(m_eTransport), m_strViaBranch.c_str(), m_eTransport);

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreateBye() {
    sip_message_t* pclsMessage = create_message(SIP_METHOD_BYE);
    if (pclsMessage == NULL) return NULL;

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreateNotify() {
    sip_message_t* pclsMessage = create_message(SIP_METHOD_NOTIFY);
    if (pclsMessage == NULL) return NULL;

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreateRefer() {
    sip_message_t* pclsMessage = create_message(SIP_METHOD_REFER);
    if (pclsMessage == NULL) return NULL;

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreatePrack() {
    if (m_iRSeq == -1) return NULL;

    sip_message_t* pclsMessage = create_message(SIP_METHOD_PRACK);
    if (pclsMessage == NULL) return NULL;

    char szRAck[101];

    snprintf(szRAck, sizeof(szRAck), "%d %d INVITE", m_iRSeq, m_iSeq);

    pclsMessage->AddHeader("RAck", szRAck);

    return pclsMessage;
}
sip_message_t* sip_dialog_t::CreateInfo() {
    sip_message_t* pclsMessage = create_message(SIP_METHOD_INFO);
    if (pclsMessage == NULL) return NULL;

    return pclsMessage;
}*/

//
// protected API. Only non-virtual methods
void sip_dialog_t::make_branch(char* buffer, int buffer_size) {
    static int counter = 0;
    if (counter <= 0 || counter > 2000000000) {
        counter = rand();
    } else {
        ++counter;
    }
    snprintf(buffer, buffer_size, "%sxxxx%x", VIA_PREFIX, counter);
}
sip_message_t sip_dialog_t::create_message(const std::string& sip_method) {
    sip_message_t sip_message;
    sip_message.mutable_call_id_hdr().set_value(m_call_id);
    sip_message.set_method(sip_method);


    sip_message.set_req_uri(sip_uri_t(m_to_user, m_to_domain, m_to_port));

    int cseq = m_iSeq;
    /*if (sip_method == SIP_METHOD_ACK && sip_method == SIP_METHOD_CANCEL) {
        if (m_iNextSeq != 0) {
            m_iSeq = m_iNextSeq;
            m_iNextSeq = 0;
        } else {
            ++m_iSeq;
        }
        cseq = m_iSeq;
    }*/
    sip_message.mutable_cseq_hdr().set_cseq(cseq);
    sip_message.mutable_cseq_hdr().set_method(sip_method);
    sip_message.mutable_from_hdr().set_uri(sip_uri_t(m_from_user, m_from_domain, m_from_port));
    sip_message.mutable_from_hdr().add_param(SIP_TAG, m_from_tag);
    sip_message.mutable_to_hdr().set_uri(sip_uri_t(m_to_user, m_to_domain, m_to_port));
	if (!m_to_tag.empty()) {
		sip_message.mutable_to_hdr().add_param(SIP_TAG, m_to_tag.c_str());
	}

	//char pai_uri[512];
	//const std::string sip_local_ip = "1.2.3.4"; // TODO: fix me
	//uint16_t sip_local_port = 5060; // TODO: fix me
	//snprintf(pai_uri, sizeof(pai_uri), "<sip:%s@%s:%d>", m_from_id.c_str(), sip_local_ip.c_str(), sip_local_port);

	//sip_message.add_header("P-Asserted-Identity", pai_uri);
	//sip_message.add_header("Diversion", pai_uri);

    /*if (m_clsRouteList.size() > 0) {
        pclsMessage->m_clsRouteList = m_clsRouteList;
    } else {
        pclsMessage->AddRoute(m_strContactIp.c_str(), m_iContactPort, m_eTransport);
    }*/

    return sip_message;
}

//
// public static API. Only static methods

//
// protected static API. Only static methods





/*bool sip_dialog_t::AddSdp(sip_message_t* pclsMessage) {
    char szSdp[4096];
    int iLen = 0;
    const char* pszAddrType = "IP4";

    if (strstr(m_strLocalRtpIp.c_str(), ":")) {
        pszAddrType = "IP6";
    }

    ++m_iSessionVersion;

    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "v=0\r\n"
                                                         "o=CSS 4 %d IN %s %s\r\n"
                                                         "s=CSS\r\n", m_iSessionVersion, pszAddrType,
                     m_strLocalRtpIp.c_str());

    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "c=IN %s %s\r\n", pszAddrType, m_strLocalRtpIp.c_str());
    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "t=0 0\r\n");

#ifdef USE_MEDIA_LIST
    if( m_clsLocalMediaList.size() > 0 )
    {
        SDP_MEDIA_LIST::iterator	itList;

        for( itList = m_clsLocalMediaList.begin(); itList != m_clsLocalMediaList.end(); ++itList )
        {
            iLen += snprintf( szSdp + iLen, sizeof(szSdp)-iLen, "m=" );
            iLen += itList->ToString( szSdp + iLen, sizeof(szSdp)-iLen );
        }
    }
    else
#endif
    {
        if (pclsMessage->IsRequest() && m_clsCodecList.empty() == false) {
            CODEC_LIST::iterator itList;

            iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "m=audio %d RTP/AVP", m_iLocalRtpPort);

            for (itList = m_clsCodecList.begin(); itList != m_clsCodecList.end(); ++itList) {
                if (IsUseCodec(*itList)) {
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, " %d", *itList);
                }
            }

            iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, " 101\r\n");

            for (itList = m_clsCodecList.begin(); itList != m_clsCodecList.end(); ++itList) {
                switch (*itList) {
                    case 0:
                        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:0 PCMU/8000\r\n");
                        break;
                    case 3:
                        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:3 GSM/8000\r\n");
                        break;
                    case 4:
                        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:4 G723/8000\r\n");
                        break;
                    case 8:
                        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:8 PCMA/8000\r\n");
                        break;
                    case 18:
                        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:18 G729/8000\r\n");
                        break;
                }
            }
        } else {
            switch (m_iCodec) {
                case 0:
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "m=audio %d RTP/AVP 0 101\r\n",
                                     m_iLocalRtpPort);
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:0 PCMU/8000\r\n");
                    break;
                case 3:
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "m=audio %d RTP/AVP 3 101\r\n",
                                     m_iLocalRtpPort);
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:3 GSM/8000\r\n");
                    break;
                case 4:
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "m=audio %d RTP/AVP 4 101\r\n",
                                     m_iLocalRtpPort);
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:4 G723/8000\r\n");
                    break;
                case 8:
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "m=audio %d RTP/AVP 8 101\r\n",
                                     m_iLocalRtpPort);
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:8 PCMA/8000\r\n");
                    break;
                case 18:
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "m=audio %d RTP/AVP 18 101\r\n",
                                     m_iLocalRtpPort);
                    iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:18 G729/8000\r\n");
                    break;
            }
        }

        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=rtpmap:101 telephone-event/8000\r\n"
                                                             "a=fmtp:101 0-15\r\n");
        iLen += snprintf(szSdp + iLen, sizeof(szSdp) - iLen, "a=%s\r\n", GetRtpDirectionString(m_eLocalDirection));
    }

    pclsMessage->m_strBody = szSdp;
    pclsMessage->m_iContentLength = iLen;
    pclsMessage->m_clsContentType.Set("application", "sdp");

    return true;
}*/

