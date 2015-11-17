// NeverEndingHeader.h
// By Matt McCarthy
#ifndef NEVERENDINGHEADER_H
#define NEVERENDINGHEADER_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::NeverEndingHeader : std::exception
{
    public:
        //! Constructs the exception.
        NeverEndingHeader() throw ();
        //! Destroys the exception.
        ~NeverEndingHeader() throw ();

        //! Returns "Never ending header".
        //! @return "Never ending header".
        const char* what() const throw ();
};

#endif
