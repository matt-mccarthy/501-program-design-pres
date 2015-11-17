// CannotConnect.h
// By Matt McCarthy
#ifndef CANNOTCONNECT_H
#define CANNOTCONNECT_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::CannotConnect : std::exception
{
    public:
        //! Constructs the exception.
        //! @param where Where the thrower cannot connect to.
        CannotConnect(std::string where) throw ();
        //! Destroys the exception.
        ~CannotConnect() throw ();

        //! Returns where the thrower is connected to.
        //! @return The server that the thrower cannot connect to.
        const char* what() const throw ();

    private:
        std::string mCantGetHere; //!< Where the thrower cannot connect to.
};

#endif

