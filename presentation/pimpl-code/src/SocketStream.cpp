// SocketStream.cpp
// By Matt McCarthy

// TODO:    Write an exception for when select() fails

#ifndef SOCKETSTREAM_CPP
#define SOCKETSTREAM_CPP

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#include "../NetLib.h"
#include "../SocketStream.h"
#include "./SocketInfo.cpp"

#include "../except/EndOfFile.h"
#include "../except/NoConnection.h"
#include "../except/SocketReadFail.h"
#include "../except/SocketWriteFail.h"
#include "../except/Timeout.h"

using std::iostream;
using std::istream;
using std::ostream;
using std::streambuf;
using std::stringstream;
using std::string;

#if __cplusplus >= 201103L
using std::move;
#endif

class NetLib::SocketStream::Socket
{
    public:
        //! Constructs the socket object.
        //! @param SockInfo The data used to make the socket.
        Socket(const SocketInfo& SockInfo, stringstream::openmode Which);
        //! Destroys the Socket.
        ~Socket();

        //! Writes to the Socket.
        //! @param WriteThis The message to write to the socket.
        //! @throw NoConnection Thrown if the socket was closed.
        //! @throw SocketWriteFail Thrown if the write operation failed.
        void Write(const string& WriteThis) throw (NoConnection, SocketWriteFail);
        //! Reads from the Socket.
        //! @param BytesToRead The amount of data to read.
        //! @return The data read from the Socket.
        //! @throw NoConnection Thrown if the socket was closed.
        //! @throw SocketReadFail Thrown if the read operation failed.
        string Read(unsigned BytesToRead) throw (NoConnection, SocketReadFail, EndOfFile, Timeout);

        //! Closes the Socket.
        void Close();
        //! Gets the socket data.
        //! @return The socket data.
        const SocketInfo& GetSocketInfo();

        stringstream IOBuffer;

    private:
        SocketInfo mSockInfo;   //!< The data that was used to make the socket.
};

// C++11 code
#if __cplusplus < 201103L

const char nullptr = 0;

#endif

NetLib::SocketStream::SocketStream() : mSocket(nullptr) {}

NetLib::SocketStream::SocketStream(const SocketInfo& SockInfo, stringstream::openmode Which) :
	mSocket(new Socket(SockInfo, Which)) {}
NetLib::SocketStream::SocketStream(const SocketInfo& SockInfo) :
	mSocket(new Socket(SockInfo,
	stringstream::in | stringstream::out | stringstream::binary)) {}

#if __cplusplus < 201103L
NetLib::SocketStream::SocketStream(const SocketStream& in) : mSocket(in.mSocket) {}
#else
NetLib::SocketStream::SocketStream(SocketStream&& in) : mSocket(in.mSocket)
{
	(in.mSocket) = nullptr;
}
#endif

NetLib::SocketStream::~SocketStream()
{
	if (mSocket != nullptr);
    	delete mSocket;
}

istream& NetLib::SocketStream::operator>>(string& in)
    throw (NoConnection, SocketReadFail, EndOfFile, Timeout)
{
    // Make sure the connection is open
    if (!(mSocket))
        throw NoConnection();

    // Read from the socket
    in = mSocket ->Read(1000);

    return (mSocket ->IOBuffer);
}

ostream& NetLib::SocketStream::operator<<(const string& in)
    throw (NoConnection, SocketWriteFail)
{
    // Make sure the connection is open
    if (!(mSocket))
        throw NoConnection();

    // Write to the socket.
    mSocket ->Write(in);

    return (mSocket ->IOBuffer);
}

#if __cplusplus < 201103L
NetLib::SocketStream& NetLib::SocketStream::operator=(const NetLib::SocketStream& in)
{
	if ((this ->mSocket) != nullptr)
		delete (this ->mSocket);

    (this ->mSocket) = (in.mSocket);

    return *this;
}
#else
NetLib::SocketStream& NetLib::SocketStream::operator=(NetLib::SocketStream&& in)
{
	if ((this ->mSocket) != nullptr)
		delete (this ->mSocket);

    (this ->mSocket) = (in.mSocket);

    (in.mSocket) = nullptr;

    return *this;
}
#endif

void NetLib::SocketStream::CloseSocket()
{
	if (mSocket != nullptr)
		delete mSocket;

    mSocket = nullptr;
}

NetLib::SocketStream::Socket::Socket(const SocketInfo& SockInfo, stringstream::openmode Which) :
	IOBuffer(Which), mSockInfo(SockInfo) {}

NetLib::SocketStream::Socket::~Socket()
{
    Close();
}

void NetLib::SocketStream::Socket::Write(const string& WriteThis)
    throw (NoConnection, SocketWriteFail)
{
    // Write and check for errors
    if(write(mSockInfo.mSocketID, WriteThis.c_str(), WriteThis.length()) == -1)
        throw SocketWriteFail(mSockInfo.mSocketID, mSockInfo.mHostName);
}

string NetLib::SocketStream::Socket::Read(unsigned BytesToRead)
    throw (NoConnection, SocketReadFail, EndOfFile, Timeout)
{
    // Create a temporary buffer
    char vBuf [BytesToRead + 1];

    memset(vBuf, 0, BytesToRead + 1);

    // Supposedly, set a timeout
    fd_set vSet;
    timeval vTimeout;
    int vReturnValue;

    FD_ZERO(&vSet); // Clear the set
    FD_SET(mSockInfo.mSocketID, &vSet); // Add the socket to the set

    vTimeout.tv_sec = 60;
    vTimeout.tv_usec = 0;

    vReturnValue = select(mSockInfo.mSocketID + 1, &vSet, nullptr, nullptr, &vTimeout);

    int vBytesRead = 0;

    // An error occured
    if (vReturnValue == -1)
        throw std::exception();

    // It timed out
    if (vReturnValue == 0)
        throw Timeout();

    // Everything went fine, now read
    else
        vBytesRead = read((mSockInfo.mSocketID), vBuf, BytesToRead);

    // Check for errors
    if (vBytesRead <= 0)
    {
        if (!vBytesRead)
            throw EndOfFile();

        throw SocketReadFail(mSockInfo.mSocketID, mSockInfo.mHostName);
    }

    // Null terminate
    vBuf[vBytesRead] = 0;

    // Initialize the out string
    string vDataOut(vBuf);

    return vDataOut;
}

void NetLib::SocketStream::Socket::Close()
{
    close(mSockInfo.mSocketID);
}

const NetLib::SocketInfo& NetLib::SocketStream::Socket::GetSocketInfo()
{
    return mSockInfo;
}


#endif
