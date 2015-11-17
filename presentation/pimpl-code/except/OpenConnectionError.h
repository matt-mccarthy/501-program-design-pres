// OpenConnectionError.h
// By Matt McCarthy
#ifndef OPENCONNECTIONERROR_H
#define OPENCONNECTIONERROR_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::OpenConnection : std::exception
{
    public:
        //! Constructs the exception.
        //! @param where Where the thrower is connected to.
        OpenConnection(std::string where) throw ();
        //! Destroys the exception.
        ~OpenConnection() throw ();

        //! Returns where the thrower is connected to.
        //! @return The server that the thrower is connected to.
        const char* what() const throw ();

    private:
        std::string mConnectedTo; //!< Where the thrower is connected to.
};

#endif
