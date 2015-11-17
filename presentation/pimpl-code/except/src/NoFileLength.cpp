// NoFileLength.cpp
// By Matt McCarthy
#ifndef NOFILELENGTH_CPP
#define NOFILELENGTH_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../NoFileLength.h"

using std::string;
using std::exception;

NetLib::NoFileLength::NoFileLength() throw () {}
NetLib::NoFileLength::~NoFileLength() throw () {}

const char* NetLib::NoFileLength::what() const throw ()
{
    return "No file length.";
}

#endif

