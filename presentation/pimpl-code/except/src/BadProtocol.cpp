// BadProtocol.cpp
// By Matt McCarthy
#ifndef BADPROTOCOL_CPP
#define BADPROTOCOL_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../BadProtocol.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::BadProtocol::BadProtocol(const string& protocolUsed) throw () : mBadProtocol(protocolUsed) {}

#else

NetLib::BadProtocol::BadProtocol(const string& protocolUsed) throw ()
{
    mBadProtocol = protocolUsed;
}

#endif

NetLib::BadProtocol::~BadProtocol() throw () {}

const char* NetLib::BadProtocol::what() const throw ()
{
    return mBadProtocol.c_str();
}

#endif


