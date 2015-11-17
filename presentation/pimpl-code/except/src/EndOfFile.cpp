// EndOfFile.cpp
// By Matt McCarthy
#ifndef ENDOFFILE_CPP
#define ENDOFFILE_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../EndOfFile.h"

NetLib::EndOfFile::EndOfFile() throw () {}
NetLib::EndOfFile::~EndOfFile() throw () {}

char* NetLib::EndOfFile::what() throw ()
{
    return "A socket has reached the end of file. Do work.";
}

#endif
