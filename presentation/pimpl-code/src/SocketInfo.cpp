// SocketInfo.cpp
// By: Matt McCarthy
#ifndef SOCKETINFO_CPP
#define SOCKETINFO_CPP

#include <netinet/in.h>
#include <netdb.h>

#include "../NetLib.h"

struct NetLib::SocketInfo
{
    //! Constructor.
    SocketInfo();
    //! Destructor.
    ~SocketInfo();

    int mSocketID;                  //!< The socket.
    std::string mHostName;          //!< The address of the server that it's connected to.
    int mPort;                      //!< The port that this is connected to.
    sockaddr_in mSocketAddress;     //!< The object containing the socket address.
    hostent mHost;                 //!< The object containing the host.
};

struct NetLib::ServerSocketInfo
{
    //! Constructor.
    ServerSocketInfo();
    //! Destructor.
    ~ServerSocketInfo();

    int mSocketID;                  //!< The socket.
    int mPort;                      //!< The port that this is connected to.
    sockaddr_in mSocketAddress;     //!< The object containing the socket address.
};

#endif
