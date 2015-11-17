// ServerSocketStream.cpp
// By: Matt McCarthy
// TODO:    Exception for unable to accept connection
//          Exception for bad listen
//          Exception for uninstantialized stream
#ifndef SERVERSOCKETSTREAM_CPP
#define SERVERSOCKETSTREAM_CPP

#include <cstring>
#include <cstdlib>

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>

#include "../NetLib.h"
#include "../ServerSocketStream.h"
#include "../SocketStream.h"
#include "./SocketInfo.cpp"

#include "../except/CannotConnect.h"
#include "../except/NoConnection.h"

class NetLib::ServerSocketStream::ServerSocket
{
    public:
        //! Constructs the socket object.
        //! @param SockInfo The data used to make the socket.
        ServerSocket(const ServerSocketInfo& SockInfo);
        //! Destroys the socket.
        ~ServerSocket();

        //! Waits indefinitely for a connection.
        //! @return A SocketStream initialized to a connection from a client.
        SocketStream GetConnection() throw (CannotConnect);

        //! Closes the socket.
        void Close();

    private:
        ServerSocketInfo mSockInfo;
};

#if __cplusplus < 201103L

const char nullptr = 0;

#endif

NetLib::ServerSocketStream::ServerSocketStream() : mSocket(nullptr) {}

NetLib::ServerSocketStream::ServerSocketStream(const ServerSocketInfo& in) :
    mSocket(new ServerSocket(in)) {}

#if __cplusplus < 201103L
NetLib::ServerSocketStream::ServerSocketStream(const ServerSocketStream& in) :
    mSocket(in.mSocket) {}
#else
NetLib::ServerSocketStream::ServerSocketStream(ServerSocketStream&& in) :
    mSocket(in.mSocket)
{
	in.mSocket = nullptr;
}
#endif

NetLib::ServerSocketStream::~ServerSocketStream()
{
	if (mSocket)
		delete mSocket;
}

NetLib::SocketStream NetLib::ServerSocketStream::ListenForConnection() throw (NoConnection, CannotConnect)
{
	if (!mSocket)
		throw NoConnection();

    return (mSocket ->GetConnection());
}

#if __cplusplus < 201103L
NetLib::ServerSocketStream& NetLib::ServerSocketStream::operator=(const ServerSocketStream& in)
{
	if (mSocket)
		delete mSocket;

	mSocket = in.mSocket;

	return *this;
}
#else
NetLib::ServerSocketStream& NetLib::ServerSocketStream::operator=(ServerSocketStream&& in)
{
	if (mSocket)
		delete mSocket;

	mSocket = in.mSocket;

	in.mSocket = nullptr;

	return *this;
}
#endif

void NetLib::ServerSocketStream::CloseSocket()
{
	if (mSocket)
	{
		mSocket ->Close();
		delete mSocket;
	}
}

NetLib::ServerSocketStream::ServerSocket::ServerSocket(const ServerSocketInfo& SockInfo)
	: mSockInfo(SockInfo) {}

NetLib::ServerSocketStream::ServerSocket::~ServerSocket()
{
    Close();
}

NetLib::SocketStream NetLib::ServerSocketStream::ServerSocket::GetConnection() throw (CannotConnect)
{
    // Listen for a connection, indefinitely
    listen(mSockInfo.mSocketID, 5);

    // Instantiate neccessary variables
    SocketInfo vNewSocket;
    socklen_t vSize = sizeof(vNewSocket.mSocketAddress);

    // Ater a connection pops up, accept
    vNewSocket.mSocketID = accept(mSockInfo.mSocketID, (sockaddr*)(&vNewSocket.mSocketAddress),
                                  &vSize);

    if (vNewSocket.mSocketID < 0) throw CannotConnect("");

    // Generate SocketInfo to create the new SocketStream

    return SocketStream(vNewSocket);
}

void NetLib::ServerSocketStream::ServerSocket::Close()
{
	shutdown(mSockInfo.mSocketID, SHUT_RDWR);
	close(mSockInfo.mSocketID);
}
#endif
