#ifndef _SIP_PARAM_H_
#define _SIP_PARAM_H_
#include "project-base.hpp"


class sip_param_t {
public:
    int parse(const char* data, int data_size);
    void reset();

    const std::string& get_name() const  { return m_name;  }
    const std::string& get_value() const { return m_value; }

protected:
    std::string m_name;
    std::string m_vaue;
};

class sip_param_list_t {
public:
    int HeaderListParamParse( const char * pszText, int iTextLen );
    int ParamParse( const char * pszText, int iTextLen );
    /*int ParamToString( char * pszText, int iTextSize, char cBeginSep = ';', char cSep = ';' );

    bool InsertParam( const char * pszName, const char * pszValue );
    bool UpdateParam( const char * pszName, const char * pszValue );
    bool SelectParam( const char * pszName, std::string & strValue );
    bool SelectParam( const char * pszName );
    const char * SelectParamValue( const char * pszName );*/

    void ClearParam();

    CSipParameterList & operator=( CSipParameterList & clsOld );

    std::list< CSipParameter * > m_clsParamList;
};


#endif // _SIP_PARAM_H_