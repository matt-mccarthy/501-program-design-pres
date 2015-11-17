// NoConnection.h
// By Matt McCarthy
#ifndef NOCONNECTION_H
#define NOCONNECTION_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::NoConnection : std::exception
{
    public:
        //! Constructs the exception.
        NoConnection() throw ();
        //! Destroys the exception.
        ~NoConnection() throw ();

        //! Returns "No connection".
        //! @return "No connection".
        const char* what() const throw ();
};

#endif
