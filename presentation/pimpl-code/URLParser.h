// URLParser.h
// By: Matt McCarthy
#ifndef URLPARSER_H
#define URLPARSER_H

#include <string>
#include <vector>

#include "./except/BadInput.h"
#include "./except/BadProtocol.h"

/// Parses a URL.
class NetLib::URLParser
{
    public:
        //! Constructs the object.
        //! @param InputURL The URL to parse.
        //! @param AllowableProtocols The allowable protocols
        //! @param DefaultPorts A list of default ports corresponding to the allowable protocols
        //! @throw BadInput Thrown if the URL is bad.
        //! @throw BadProtocol Thrown if the protocol used is disallowed.
        URLParser(std::string InputURL, std::vector<std::string> AllowableProtocols, std::vector<int> DefaultPorts)
            throw (BadInput, BadProtocol);
        //! Destroys the object.
        ~URLParser();

        //! Gets the hostname.
        //! @return The hostname.
        std::string GetHostAddress();
        //! Gets the resource path.
        //! @return The resource path.
        std::string GetPath();
        //! Gets the protocol used.
        //! @return the protocol used.
        std::string GetProtocol();
        //! Gets the port used.
        //! @return The port used.
        int GetPort();

    private:
        std::string mHostAddress;   //!< The hostname.
        std::string mPath;          //!< The resource path.
        std::string mProtocol;      //!< The protocol used.
        int mPort;                  //!< The port used.
};

#endif
