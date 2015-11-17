// BadHost.cpp
// By Matt McCarthy
#ifndef BADSOCKET_CPP
#define BADSOCKET_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../BadSocket.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::BadSocket::BadSocket(string except) throw () : mExcept(except) {}

#else

NetLib::BadSocket::BadSocket(string except) throw () : mExcept(except)
{
    mExcept = except;
}

#endif

NetLib::BadSocket::~BadSocket() throw () {}

const char* NetLib::BadSocket::what() const throw ()
{
    return mExcept.c_str();
}

#endif
