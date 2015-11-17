// Timeout.cpp
// By Matt McCarthy
#ifndef TIMEOUT_CPP
#define TIMEOUT_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../Timeout.h"

NetLib::Timeout::Timeout() throw () {}
NetLib::Timeout::~Timeout() throw () {}

char* NetLib::Timeout::what() throw ()
{
    return "A socket has timed out. Do work.";
}

#endif

