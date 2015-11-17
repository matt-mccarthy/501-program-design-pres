// BadHost.cpp
// By Matt McCarthy
#ifndef BADHOST_CPP
#define BADHOST_CPP

#include <string>
#include <exception>

#include "../../NetLib.h"
#include "../BadHost.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::BadHost::BadHost(string badHostName) throw () : mBadHostName(badHostName) {}

#else

NetLib::BadHost::BadHost(string badHostName) throw ()
{
    mBadHostName = badHostName;
}

#endif

NetLib::BadHost::~BadHost() throw () {}

const char* NetLib::BadHost::what() const throw ()
{
    return mBadHostName.c_str();
}

#endif
