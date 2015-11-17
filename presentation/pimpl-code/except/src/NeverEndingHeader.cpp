// NeverEndingHeader.cpp
// By Matt McCarthy
#ifndef NEVERENDINGHEADER_CPP
#define NEVERENDINGHEADER_CPP

#include <exception>
#include <string>

#include "../../NetLib.h"
#include "../NeverEndingHeader.h"

using std::string;
using std::exception;

NetLib::NeverEndingHeader::NeverEndingHeader() throw () {}

NetLib::NeverEndingHeader::~NeverEndingHeader() throw () {}

const char* NetLib::NeverEndingHeader::what() const throw ()
{
    return "Never ending header.";
}

#endif

