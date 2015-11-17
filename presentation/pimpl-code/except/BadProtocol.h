// BadProtocol.h
// By Matt McCarthy
#ifndef BADPROTOCOL_H
#define BADPROTOCOL_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::BadProtocol : std::exception
{
    public:
        //! Sets up the exception.
        //! @param protocolUsed The bad protocol.
        BadProtocol(const std::string& protocolUsed) throw ();
        //! Destroys the exception
        ~BadProtocol() throw ();

        //! Gets the bad protocol.
        //! @return The bad protocol.
        const char* what() const throw ();

    private:
        std::string mBadProtocol; //!< The bad protocol.
};

#endif

