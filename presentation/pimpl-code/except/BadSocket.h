// BadSocket.h
// By Matt McCarthy
#ifndef BADSOCKET_H
#define BADSOCKET_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::BadSocket : std::exception
{
    public:
        //! Sets up the exception.
        //! @param except The problem with the socket.
        BadSocket(std::string except) throw ();
        //! Destroys the exception
        ~BadSocket() throw ();

        //! Gets the problem with the socket.
        //! @return The problem.
        const char* what() const throw ();

    private:
        std::string mExcept; //!< The problem with the socket.
};

#endif
