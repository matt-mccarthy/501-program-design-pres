// Timeout.h
// By Matt McCarthy
#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <exception>
#include <string>

#include "../NetLib.h"

class NetLib::Timeout : std::exception
{
    public:
        Timeout() throw ();
        ~Timeout() throw ();

        char* what() throw ();

    private:
};

#endif

