// CannotConnect.cpp
// By Matt McCarthy
#ifndef CANNOTCONNECT_CPP
#define CANNOTCONNECT_CPP

#include <string>
#include <exception>

#include "../../NetLib.h"
#include "../CannotConnect.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::CannotConnect::CannotConnect(string where) throw () : mCantGetHere(where) {}

#else

NetLib::CannotConnect::CannotConnect(string where) throw ()
{
    mCantGetHere = where;
}

#endif

NetLib::CannotConnect::~CannotConnect() throw () {}

const char* NetLib::CannotConnect::what() const throw ()
{
    return mCantGetHere.c_str();
}

#endif
