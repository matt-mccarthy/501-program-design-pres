#ifndef SOCKETSTREAM_H
#define SOCKETSTREAM_H
// SocketStream.h
// By Matt McCarthy

#include <memory>
#include <string>
#include <sstream>

#include "./NetLib.h"
#include "./except/EndOfFile.h"
#include "./except/NoConnection.h"
#include "./except/SocketReadFail.h"
#include "./except/SocketWriteFail.h"
#include "./except/Timeout.h"


class NetLib::SocketStream
{
    public:
        //! Constructs an empty SocketStream.
        SocketStream();
        //! Constructs a SocketStream. The socket used must be open.
        //! @param SockInfo The information used to open the socket.
        //! @param Which The openmode for the stream.
        SocketStream(const SocketInfo& SockInfo, std::stringstream::openmode Which);
        //! Constructs a socket stream. The socket used must be open.
        //! @param SockInfo The information used to open the socket.
        SocketStream(const SocketInfo& SockInfo);

        #if __cplusplus < 201103L
        //! Copy constructor.
        //! @param in The SocketStream to copy.
        SocketStream(const SocketStream& in);
        #else
        //! Move constructor.
        //! @param in The SocketStream to move.
        SocketStream(SocketStream&& in);
        #endif

        //! Destroys the SocketStream.
        ~SocketStream();

        //! Write data from a STL string to the socket.
        //! @param in The string to read from.
        //! @throw NoConnection Thrown if this SocketStream was closed.
        //! @throw SocketWriteFail Thrown if the write operation fails.
        std::ostream& operator<<(const std::string& in) throw (NoConnection, SocketWriteFail);
        //! Read data from the socket to a STL string.
        //! @param in The string to write to.
        //! @throw NoConnection Thrown if this SocketStream was closed.
        //! @throw SocketWriteFail Thrown if the read operation fails.
        std::istream& operator>>(std::string& in) throw (NoConnection, SocketReadFail, EndOfFile, Timeout);
        #if __cplusplus < 201103L
        SocketStream& operator=(const SocketStream& in);
        #else
        SocketStream& operator=(SocketStream&& in);
        #endif

        //! Closes the SocketStream.
        void CloseSocket();

    private:
        //! The socket that this SocketStream interfaces with.
        class Socket;
        Socket* mSocket; //!< The socket that this interfaces with.
};

#endif
