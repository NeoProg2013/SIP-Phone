#ifndef _SIP_CODES_H_
#define _SIP_CODES_H_
#include "global-env.hpp"

static const uint16_t SIP_TRYING                        = 100;
static const uint16_t SIP_RINGING                       = 180;
static const uint16_t SIP_CALL_IS_BEING_FORWARDED       = 181;
static const uint16_t SIP_QUEUED                        = 182;
static const uint16_t SIP_SESSION_PROGRESS              = 183;
static const uint16_t SIP_OK                            = 200;
static const uint16_t SIP_ACCEPTED                      = 202;
static const uint16_t SIP_MULTIPLE_CHOICES              = 300;
static const uint16_t SIP_MOVED_PERMANENTLY             = 301;
static const uint16_t SIP_MOVED_TEMPORARILY             = 302;
static const uint16_t SIP_USE_PROXY                     = 305;
static const uint16_t SIP_ALTERNATIVE_SERVICE           = 380;
static const uint16_t SIP_BAD_REQUEST                   = 400;
static const uint16_t SIP_UNAUTHORIZED                  = 401;
static const uint16_t SIP_PAYMENT_REQUIRED              = 402;
static const uint16_t SIP_FORBIDDEN                     = 403;
static const uint16_t SIP_NOT_FOUND                     = 404;
static const uint16_t SIP_METHOD_NOT_ALLOWED            = 405;
static const uint16_t SIP_NOT_ACCEPTABLE                = 406;
static const uint16_t SIP_PROXY_AUTHENTICATION_REQUIRED = 407;
static const uint16_t SIP_REQUEST_TIME_OUT              = 408;
static const uint16_t SIP_CONFLICT                      = 409;
static const uint16_t SIP_GONE                          = 410;
static const uint16_t SIP_LENGTH_REQUIRED               = 411;
static const uint16_t SIP_CONDITIONAL_REQUEST_FAILED    = 412;
static const uint16_t SIP_REQUEST_ENTITY_TOO_LARGE      = 413;
static const uint16_t SIP_REQUEST_URI_TOO_LARGE         = 414;
static const uint16_t SIP_UNSUPPORTED_MEDIA_TYPE        = 415;
static const uint16_t SIP_UNSUPPORTED_URI_SCHEME        = 416;
static const uint16_t SIP_BAD_EXTENSION                 = 420;
static const uint16_t SIP_EXTENSION_REQUIRED            = 421;
static const uint16_t SIP_SESSION_INTERVAL_TOO_SMALL    = 422;
static const uint16_t SIP_INTERVAL_TOO_BRIEF            = 423;
static const uint16_t SIP_TEMPORARILY_UNAVAILABLE       = 480;
static const uint16_t SIP_CALL_TRANSACTION_DOES_NOT_EX  = 481;
static const uint16_t SIP_LOOP_DETECTED                 = 482;
static const uint16_t SIP_TOO_MANY_HOPS                 = 483;
static const uint16_t SIP_ADDRESS_INCOMPLETE            = 484;
static const uint16_t SIP_AMBIGUOUS                     = 485;
static const uint16_t SIP_BUSY_HERE                     = 486;
static const uint16_t SIP_REQUEST_TERMINATED            = 487;
static const uint16_t SIP_NOT_ACCEPTABLE_HERE           = 488;
static const uint16_t SIP_BAD_EVENT                     = 489;
static const uint16_t SIP_REQUEST_PENDING               = 491;
static const uint16_t SIP_UNDECIPHERABLE                = 493;
static const uint16_t SIP_INTERNAL_SERVER_ERROR         = 500;
static const uint16_t SIP_NOT_IMPLEMENTED               = 501;
static const uint16_t SIP_BAD_GATEWAY                   = 502;
static const uint16_t SIP_SERVICE_UNAVAILABLE           = 503;
static const uint16_t SIP_SERVER_TIME_OUT               = 504;
static const uint16_t SIP_VERSION_NOT_SUPPORTED         = 505;
static const uint16_t SIP_MESSAGE_TOO_LARGE             = 513;
static const uint16_t SIP_BUSY_EVERYWHERE               = 600;
static const uint16_t SIP_DECLINE                       = 603;
static const uint16_t SIP_DOES_NOT_EXIST_ANYWHERE       = 604;
static const uint16_t SIP_CONNECT_ERROR                 = 660;
static const uint16_t SIP_RING_TIMEOUT_ERROR            = 661;


std::string get_reason_phrase(int code);


#endif // _SIP_CODES_H_
