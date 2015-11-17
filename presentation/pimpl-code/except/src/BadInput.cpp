// BadInput.cpp
// By Matt McCarthy
#ifndef BADINPUT_CPP
#define BADINPUT_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../BadInput.h"

using std::string;
using std::exception;

#if __cplusplus >= 201103L

NetLib::BadInput::BadInput(const string& whereTo) throw () : mBadURL(whereTo) {}

#else

NetLib::BadInput::BadInput(const string& whereTo) throw ()
{
    mBadURL = whereTo;
}

#endif

NetLib::BadInput::~BadInput() throw () {}

const char* NetLib::BadInput::what() const throw ()
{
    return mBadURL.c_str();
}

#endif

