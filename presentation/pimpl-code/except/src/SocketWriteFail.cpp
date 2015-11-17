// BadHost.cpp
// By Matt McCarthy
#ifndef SOCKETWRITEFAIL_CPP
#define SOCKETWRITEFAIL_CPP

#include <string>
#include <exception>

#include "../../NetLib.h"
#include "../SocketWriteFail.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::SocketWriteFail::SocketWriteFail(int socketID, string whereTo) throw () :
    mWhereTo(whereTo), mSocketID(socketID) {}

#else

NetLib::SocketWriteFail::SocketWriteFail(int socketID, string whereTo) throw ()
{
    mWhereTo = whereTo;
    mSocketID = socketID;
}

#endif

NetLib::SocketWriteFail::~SocketWriteFail() throw () {}

const char* NetLib::SocketWriteFail::what() const throw ()
{
    return mWhereTo.c_str();
}

int NetLib::SocketWriteFail::whatSocket() const throw ()
{
    return mSocketID;
}

#endif
