// BadInput.h
// By Matt McCarthy
#ifndef BADINPUT_H
#define BADINPUT_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::BadInput : std::exception
{
    public:
        //! Sets up the exception.
        //! @param whereTo The bad address.
        BadInput(const std::string& whereTo) throw ();
        //! Destroys the exception
        ~BadInput() throw ();

        //! Gets the bad address.
        //! @return The the bad address.
        const char* what() const throw ();

    private:
        std::string mBadURL; //!< The problem with the socket.
};

#endif
