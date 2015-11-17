// NetLib.h
// By Matt McCarthy
// NetLib API
// Runs under C++11 standard
// Compiled with g++ 4.6 for x64 Linux
// g++ -std=c++0x

#ifndef NETLIB_H
#define NETLIB_H

#include <iostream>

namespace NetLib
{
    // Main classes
    /// Splits URLs into parts.
    class URLParser;
    /// Allows for socket I/O.
    class SocketStream;
	/// A SocketStream for a server.
	class ServerSocketStream;

	// Uninstantiables
    /// Contains all data that was used to make a socket.
    struct SocketInfo;
	/// Contains all data that was used to make a listening socket.
    struct ServerSocketInfo;

    // Exceptions
    /// Thrown if the host name cannot be found.
    class BadHost;
    /// Thrown if the URL is invalid.
    class BadInput;
    /// Thrown if the protocol used is invalid.
    class BadProtocol;
    /// Thrown if a socket was unable to be made.
    class BadSocket;
    /// Thrown on socket bind error.
    class BindError;
    /// Thrown if a connection failed.
    class CannotConnect;
    /// Thrown when EOF is found.
    class EndOfFile;
    /// Thrown if a downloaded header is improperly terminated.
    class NeverEndingHeader;
    /// Thrown if a disconnected SocketStream is used.
    class NoConnection;
    /// There is no "Content-Length" field in a downloaded header.
    class NoFileLength;
    /// Thrown if a connection is not properly closed. (Unused).
    class OpenConnection;
    /// Thrown if a  socket read attempt failed.
    class SocketReadFail;
    /// Thrown if a socket write attempt failed.
    class SocketWriteFail;
    /// Thrown if a socket times out
    class Timeout;

    // Functions
    /// Connects to a server.
    /// @param ConnectTo The host to connect to.
    /// @param Port The port to connect to.
    /// @return A SocketStream that supports I/O operations in binary mode.
    /// @throw CannotConnect Thrown if it can't connect.
    /// @throw BadHost Thrown if the host name is bad.
    /// @throw BadSocket Thrown if the socket cannot be made.
    SocketStream Connect(const std::string& ConnectTo, int Port)
        throw (BadHost, BadSocket, CannotConnect);

    /// Creates a server socket.
    /// @param Port The port to listen on.
    /// @return A server socket that is bound to port Port.
    /// @throw BadSocket Thrown when there's an error in creating the socket.
    ServerSocketStream MakeServerSocket(unsigned Port)
        throw (BadSocket, BindError);

    // Operators
    /// Used to insert data into a SocketStream from an istream.
    /// @param InStream The stream to read from.
    /// @param SockStream The socket to write to.
    /// @return InStream.
    /// @throw NoConnection Thrown if SockStream was already closed.
    /// @throw SocketWriteFail Thrown if the write operation fails.
    std::istream& operator>>(std::istream& InStream, SocketStream& SockStream)
        throw (NoConnection, SocketWriteFail);
    /// Used to read data from a SocketStream to an ostream.
    /// @param OutStream The stream to write to.
    /// @param SockStream The socket to read from.
    /// @return OutStream
    /// @throw NoConnection Thrown if SockStream was already closed.
    /// @throw SocketReadFail Thrown if the write operation fails.
    std::ostream& operator<<(std::ostream& OutStream, SocketStream& SockStream)
        throw (NoConnection, SocketReadFail);
}

#endif
