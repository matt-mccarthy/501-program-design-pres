// EndOfFile.h
// By Matt McCarthy
#ifndef ENDOFFILE_H
#define ENDOFFILE_H

#include <exception>
#include <string>

#include "../NetLib.h"

class NetLib::EndOfFile : std::exception
{
    public:
        EndOfFile() throw ();
        ~EndOfFile() throw ();

        char* what() throw ();

    private:
};

#endif
