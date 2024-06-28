#ifndef _SIP_STACK_H_
#define _SIP_STACK_H_
#include "global-env.hpp"
#include "sip-message.hpp"


class sipstack_t {
//
// public virtual API and ctors
public:
	sipstack_t();
	virtual ~sipstack_t();

//
// protected virtual API. Only virtual methods and ctors
protected:

//
// public API. Only non-virtual methods
public:
	bool init();
	void tick();

//
// protected API. Only non-virtual methods
protected:

//
// public static API. Only static methods
public:

//
// protected static API. Only static methods
protected:

protected:

};


#endif // _SIP_STACK_H_