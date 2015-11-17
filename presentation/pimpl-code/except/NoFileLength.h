// NoFileLength.h
// By Matt McCarthy
#ifndef NOFILELENGTH_H
#define NOFILELENGTH_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::NoFileLength : std::exception
{
    public:
        //! Constructs the exception.
        NoFileLength() throw ();
        //! Destroys the exception.
        ~NoFileLength() throw ();

        //! Returns "No file length".
        //! @return "No file length".
        const char* what() const throw ();
};

#endif

