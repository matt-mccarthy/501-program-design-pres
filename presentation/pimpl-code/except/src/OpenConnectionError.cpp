// OpenConnectionError.cpp
// By Matt McCarthy
#ifndef OPENCONNECTIONERROR_CPP
#define OPENCONNECTIONERROR_CPP

#include <string>
#include <exception>

#include "../../NetLib.h"
#include "../OpenConnectionError.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::OpenConnection::OpenConnection(string where) throw () : mConnectedTo(where) {}

#else

NetLib::OpenConnection::OpenConnection(string where) throw ()
{
    mConnectedTo = where;
}

#endif

NetLib::OpenConnection::~OpenConnection() throw () {}

const char* NetLib::OpenConnection::what() const throw ()
{
    return mConnectedTo.c_str();
}

#endif
