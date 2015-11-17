// SocketWriteFail.h
// By Matt McCarthy
#ifndef SOCKETWRITEFAIL_H
#define SOCKETWRITEFAIL_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::SocketWriteFail : std::exception
{
    public:
        //! Constructs the exception.
        //! @param socketID The socket that failed it's writing test.
        //! @param whereTo Where the failure of a socket is connected to.
        SocketWriteFail(int socketID, std::string whereTo) throw ();
        //! Destroys the exception.
        ~SocketWriteFail() throw ();

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
