// BindError.h
// By: Matt McCarthy
#ifndef BINDERROR_H
#define BINDERROR_H

#include <exception>

#include "../NetLib.h"

class NetLib::BindError : std::exception
{
	public:
		BindError() throw ();
		~BindError() throw ();
		
		const char* what() throw();
};

#endif
