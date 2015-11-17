// NetLib.cpp
// By Matt McCarthy
#ifndef NETLIB_CPP
#define NETLIB_CPP

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

#include "../NetLib.h"
#include "../SocketStream.h"
#include "../ServerSocketStream.h"

#include "../except/CannotConnect.h"
#include "../except/BadHost.h"
#include "../except/BadSocket.h"
#include "../except/BindError.h"

#include "./SocketInfo.cpp"

using std::istream;
using std::ostream;
using std::stringstream;
using std::string;

#if __cplusplus < 201103L

const char nullptr = 0;

#endif

// Implementation prototypes
int CreateConnection(const char* connectTo, int port, hostent& host,
                     sockaddr_in& socketAddress) throw(NetLib::BadHost, NetLib::BadSocket);

hostent* FindHost(const char* connectTo);

sockaddr_in MakeSocketAddress(const hostent* host, int port);

int MakeSocket(const hostent* host, const sockaddr_in& socketAddress);

// Free function implementations
NetLib::SocketStream NetLib::Connect(const string& ConnectTo, int Port)
    throw (BadHost, BadSocket, CannotConnect)
{

    // Make a struct that contains all the data needed to make a socket
    SocketInfo vNewSocket;

    // Set up the SocketInfo
    vNewSocket.mHostName = ConnectTo;
    vNewSocket.mPort = Port;

    // Make the connection
    vNewSocket.mSocketID = CreateConnection(ConnectTo.c_str(), Port, vNewSocket.mHost,
                               vNewSocket.mSocketAddress);

    // Connect
    if (connect(vNewSocket.mSocketID, (sockaddr*) &(vNewSocket.mSocketAddress),
                sizeof(vNewSocket.mSocketAddress)))
    {
    	//vNewSocket.mSocketAddress = nullptr;
        throw CannotConnect(ConnectTo);
    }

	SocketStream vSocketInterface(vNewSocket);

    return vSocketInterface;
}

NetLib::ServerSocketStream NetLib::MakeServerSocket(unsigned Port) throw (BadSocket, BindError)
{
    // Make a struct that contains all info needed to make a server socket.
    ServerSocketInfo vNewSocket;
    vNewSocket.mPort = Port;

	memset((void *) (&vNewSocket.mSocketAddress), 0, sizeof(vNewSocket.mSocketAddress));
    vNewSocket.mSocketAddress.sin_family = AF_INET;
    vNewSocket.mSocketAddress.sin_addr.s_addr = INADDR_ANY;
    vNewSocket.mSocketAddress.sin_port = htons(Port);

    // Make the socket.
    vNewSocket.mSocketID = socket(AF_INET, SOCK_STREAM, 0);

    if (vNewSocket.mSocketID < 0) throw BadSocket("");

//	int one = 1;

    // Allow the port to be reused on exit
//    if (setsockopt((vNewSocket.mSocketID), SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0);
//        throw 2; // Thrown on set option error

    // Bind the socket.
    if (bind(vNewSocket.mSocketID, (sockaddr*)(&(vNewSocket.mSocketAddress)),
             sizeof(vNewSocket.mSocketAddress)) < 0)
        throw BindError(); // Thrown on bind error.

    return ServerSocketStream(vNewSocket);
}

istream& NetLib::operator>>(istream& InStream, SocketStream& SockStream)
    throw (NoConnection, SocketWriteFail)
{
    string vBufStream;

    // Move InStream into the buffer stream.
    InStream >> vBufStream;

    // Move the buffer stream into SockStream.
    SockStream << vBufStream;

    return InStream;
}

ostream& NetLib::operator<<(ostream& OutStream, SocketStream& SockStream)
    throw (NoConnection, SocketReadFail)
{
    string vBufStream;

    // Read from SockStream to the buffer stream.
    SockStream >> vBufStream;

    // Write the buffer stream to OutStream.
    OutStream << vBufStream;

    return OutStream;
}

NetLib::SocketInfo::SocketInfo() : mSocketID(-1), mHostName(""), mPort(-1),
    mSocketAddress(), mHost() {}

NetLib::SocketInfo::~SocketInfo() {}

NetLib::ServerSocketInfo::ServerSocketInfo() : mSocketID(-1), mPort(-1), mSocketAddress() {}

NetLib::ServerSocketInfo::~ServerSocketInfo() {}


// Implementation functions

// Leaky function
int CreateConnection(const char* connectTo, int port, hostent& host,
                     sockaddr_in& socketAddress)
                     throw(NetLib::BadHost, NetLib::BadSocket)
{
    // Find the hostname
    hostent* vHostPtr = FindHost(connectTo);

    if(vHostPtr == nullptr)
        throw NetLib::BadHost(connectTo);

	host = *vHostPtr;

    // Make an internet socket address
    socketAddress = MakeSocketAddress(&host, port);

    // Make a socket
    int vSocket = MakeSocket(&host, socketAddress);

    if(vSocket == -1)
        throw NetLib::BadSocket("");

    return vSocket;
}

hostent* FindHost(const char* connectTo)
{
    // Get the host name
    hostent* vHost = gethostbyname(connectTo);
    return vHost;
}

sockaddr_in MakeSocketAddress(const hostent* host, int port)
{
    // Declare variables
    sockaddr_in vSocketAddress;

    // Set the connection port
    vSocketAddress.sin_port = htons(port);

    // Initialize vSocketAddress.sin_zero to 0
    memset(vSocketAddress.sin_zero, 0, sizeof(vSocketAddress.sin_zero));

    // Get the address and it's type from the host
    vSocketAddress.sin_addr.s_addr = *((unsigned long *)(host->h_addr_list[0]));
    vSocketAddress.sin_family = host ->h_addrtype;

    return vSocketAddress;
}

int MakeSocket(const hostent* host, const sockaddr_in& socketAddress)
{
    return socket(host ->h_addrtype, SOCK_STREAM, 0);
}

#endif
