// SocketReadFail.h
// By Matt McCarthy
#ifndef SOCKETREADFAIL_H
#define SOCKETREADFAIL_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::SocketReadFail : std::exception
{
    public:
        //! Constructs the exception.
        //! @param socketID The socket that failed it's reading test.
        //! @param whereTo Where the failure of a socket is connected to.
        SocketReadFail(int socketID, std::string whereTo) throw ();
        //! Destroys the exception.
        ~SocketReadFail() throw ();

        //! Gets where the thrower is conencted to.
        //! @return The address of the server that the thrower is connected to.
        const char* what() const throw ();
        //! Gets the failure of a socket.
        //! @return The socket that failed.
        int whatSocket() const throw ();

    private:
        std::string mWhereTo;   //!< Where the thrower is connected to.
        int mSocketID;          //!< The failing socket.
};

#endif

