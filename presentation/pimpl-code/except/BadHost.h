// BadHost.h
// By Matt McCarthy
#ifndef BADHOST_H
#define BADHOST_H

#include <string>
#include <exception>

#include "../NetLib.h"

class NetLib::BadHost : std::exception
{
    public:
        //! Sets up the exception.
        //! @param badHostName The name of the host.
        BadHost(std::string badHostName) throw ();
        //! Destroys the exception
        ~BadHost() throw ();
        //! Gets the problem host.
        //! @return The problem host.
        const char* what() const throw ();
    private:
        const std::string mBadHostName; //!< The problem host name.
};

#endif
