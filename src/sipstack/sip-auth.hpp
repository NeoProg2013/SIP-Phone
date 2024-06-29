#ifndef _SIP_AUTH_H_
#define _SIP_AUTH_H_
#include "global-env.hpp"
#include "sip-credential-hdr.hpp"
#include "md5.hpp"



std::string array_to_hex_string(const uint8_t* a, int len) {
	std::string s;
	for (int i = 0; i < len; ++i) {
		char buffer[3] = { 0 };
		_itoa_s<3>(a[i], buffer, 16);
		if (buffer[1] == '\0') {
			s += '0';
			s += buffer[0];
		} else {
			s += buffer[0];
			s += buffer[1];
		}
	}
	return s;
}

bool add_auth(const sip_credential_hdr_t& challenge, const std::string& method, const std::string& user_name, const std::string& domain,
	          const std::string& pwd, sip_credential_hdr_t* response) {

	const std::string cnonce = "0a4f113b";

	uint8_t md5_buffer[16] = { 0 };

	std::string a1 = user_name + ":" + challenge.m_realm + ":" + pwd;
	std::cout << a1 << std::endl;
	md5(a1.c_str(), a1.size(), md5_buffer);
	a1 = array_to_hex_string(md5_buffer, 16);
	std::cout << a1 << std::endl;

	std::string a2 = method + ":sip:" + domain;
	std::cout << a2 << std::endl;
	md5(a2.c_str(), a2.size(), md5_buffer);
	a2 = array_to_hex_string(md5_buffer, 16);
	std::cout << a2 << std::endl;

	std::string a3 = a1 + ":" + challenge.m_nonce + ":" + "00000001" + ":" + cnonce + ":" + challenge.m_qop + ":" + a2;
	std::cout << a3 << std::endl;
	md5(a3.c_str(), a3.size(), md5_buffer);
	a3 = array_to_hex_string(md5_buffer, 16);
	std::cout << a3 << std::endl;


	response->m_type = challenge.m_type;
	response->m_realm = challenge.m_realm;
	response->m_nonce = challenge.m_nonce;
	response->m_algorithm = challenge.m_algorithm;
	response->m_qop = challenge.m_qop;
	response->m_uri = "sip:" + domain;
	response->m_user_name = user_name;
	response->m_response = a3;
	response->m_cnonce = cnonce;





	/*snprintf(szResponse, sizeof(szResponse), "%s:%s:%s:%s:%s:%s", szA1, pclsCredential->m_strNonce.c_str(), pclsCredential->m_strNonceCount.c_str()
		, pclsCredential->m_strCnonce.c_str(), pclsCredential->m_strQop.c_str(), szA2);
	SipMd5String(szResponse, szMd5);
	snprintf(szResponse, sizeof(szResponse), "%s", szMd5);*/


	//snprintf(szA1, sizeof(szA1), "%s:%s:%s", pclsCredential->m_strUserName.c_str(), pclsCredential->m_strRealm.c_str(), m_strPassWord.c_str());
	//SipMd5String(szA1, szMd5);



    return true;
    /**response = request;

    response->m_user = user;
    response->m_uri = "sip:" + domain;
    if (response->m_qop == "auth") {

    }


    response->m_uri = "sip:";
    response->m_uri.append(domain);

    char	szA1[1024], szA2[1024], szMd5[33], szResponse[1024];
    const char * pszQop = pclsChallenge->m_strQop.c_str();

    if( pclsChallenge->m_strQop.empty() == false && !strncmp( pszQop, "auth", 4 ) )
    {
        STRING_LIST clsQopList;

        // qop="auth,auth-int" ·О АФ·ВµЗѕъА» ¶§їЎ ё¶Бцё· ЗЧёсА» ј±ЕГЗСґЩ.
        if( strstr( pszQop, "," ) )
        {
            SplitString( pszQop, clsQopList, ',' );

            STRING_LIST::iterator itSL;

            for( itSL = clsQopList.begin(); itSL != clsQopList.end(); ++itSL )
            {
                pclsCredential->m_strQop = *itSL;
            }
        }
        else
        {
            pclsCredential->m_strQop = pclsChallenge->m_strQop;
        }

        char szNonceCount[9];

        snprintf( szNonceCount, sizeof(szNonceCount), "%08d", iNonceCount );
        pclsCredential->m_strNonceCount = szNonceCount;
        pclsCredential->m_strCnonce = "1";

        snprintf( szA1, sizeof(szA1), "%s:%s:%s", pclsCredential->m_strUserName.c_str(), pclsCredential->m_strRealm.c_str(), m_strPassWord.c_str() );
        SipMd5String( szA1, szMd5 );
        snprintf( szA1, sizeof(szA1), "%s", szMd5 );

        // http://qnimate.com/understanding-http-authentication-in-depth/
        if( !strcmp( pclsCredential->m_strQop.c_str(), "auth-int" ) )
        {
            SipMd5String( pclsRequest->m_strBody.c_str(), szMd5 );
            snprintf( szA2, sizeof(szA2), "%s:%s:%s", pclsRequest->m_strSipMethod.c_str(), pclsCredential->m_strUri.c_str(), szMd5 );
        }
        else
        {
            snprintf( szA2, sizeof(szA2), "%s:%s", pclsRequest->m_strSipMethod.c_str(), pclsCredential->m_strUri.c_str() );
        }

        SipMd5String( szA2, szMd5 );
        snprintf( szA2, sizeof(szA2), "%s", szMd5 );

        snprintf( szResponse, sizeof(szResponse), "%s:%s:%s:%s:%s:%s", szA1, pclsCredential->m_strNonce.c_str(), pclsCredential->m_strNonceCount.c_str()
                , pclsCredential->m_strCnonce.c_str(), pclsCredential->m_strQop.c_str(), szA2 );
        SipMd5String( szResponse, szMd5 );
        snprintf( szResponse, sizeof(szResponse), "%s", szMd5 );

        pclsCredential->m_strResponse = szMd5;
    }
    else
    {
        snprintf( szA1, sizeof(szA1), "%s:%s:%s", pclsCredential->m_strUserName.c_str(), pclsCredential->m_strRealm.c_str(), m_strPassWord.c_str() );
        SipMd5String( szA1, szMd5 );
        snprintf( szA1, sizeof(szA1), "%s", szMd5 );

        snprintf( szA2, sizeof(szA2), "%s:%s", pclsRequest->m_strSipMethod.c_str(), pclsCredential->m_strUri.c_str() );
        SipMd5String( szA2, szMd5 );
        snprintf( szA2, sizeof(szA2), "%s", szMd5 );

        snprintf( szResponse, sizeof(szResponse), "%s:%s:%s", szA1, pclsCredential->m_strNonce.c_str(), szA2 );
        SipMd5String( szResponse, szMd5 );

        pclsCredential->m_strResponse = szMd5;
    }

    if( iStatusCode == SIP_PROXY_AUTHENTICATION_REQUIRED )
    {
        pclsRequest->m_clsProxyAuthorizationList.push_front( pclsCredential );
    }
    else
    {
        pclsRequest->m_clsAuthorizationList.push_front( pclsCredential );
    }

    return true;*/
}


#endif // _SIP_AUTH_HDR_H_