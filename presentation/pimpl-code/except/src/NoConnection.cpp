// NoConnection.cpp
// By Matt McCarthy
#ifndef NOCONNECTION_CPP
#define NOCONNECTION_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../NoConnection.h"

using std::string;
using std::exception;

NetLib::NoConnection::NoConnection() throw () {}
NetLib::NoConnection::~NoConnection() throw () {}

const char* NetLib::NoConnection::what() const throw ()
{
    return "Not connected";
}

#endif
