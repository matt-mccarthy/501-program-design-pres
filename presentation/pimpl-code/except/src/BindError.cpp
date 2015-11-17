// BindError.cpp
// By: Matt McCarthy
#ifndef BINDERROR_CPP
#define BINDERROR_CPP

#include "../../NetLib.h"
#include "../BindError.h"

NetLib::BindError::BindError() throw () {}

NetLib::BindError::~BindError() throw () {}

const char* NetLib::BindError::what() throw ()
{
	return "Cannot bind listening socket.";
}

#endif
