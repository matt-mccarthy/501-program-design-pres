// BadHost.cpp
// By Matt McCarthy
#ifndef SOCKETREADFAIL_CPP
#define SOCKETREADFAIL_CPP

#include <string>
#include <exception>

#include "../../NetLib.h"
#include "../SocketReadFail.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::SocketReadFail::SocketReadFail(int socketID, string whereTo) throw () :
    mWhereTo(whereTo), mSocketID(socketID) {}

#else

NetLib::SocketReadFail::SocketReadFail(int socketID, string whereTo) throw ()
{
    mWhereTo = whereTo;
    mSocketID = socketID;
}

#endif

NetLib::SocketReadFail::~SocketReadFail() throw () {}

const char* NetLib::SocketReadFail::what() const throw ()
{
    return mWhereTo.c_str();
}

int NetLib::SocketReadFail::whatSocket() const throw ()
{
    return mSocketID;
}

#endif

