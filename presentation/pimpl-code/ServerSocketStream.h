#ifndef SERVERSOCKETSTREAM_H
#define SERVERSOCKETSTREAM_H

#include "./NetLib.h"

class NetLib::ServerSocketStream
{
	public:
		/// Creates an empty ServerSocketStream.
		ServerSocketStream();
		/// Creates a ServerSocketStream that listens on a port.
		/// @param in The info that constructed this.
		ServerSocketStream(const ServerSocketInfo& in);

		#if __cplusplus < 201103L
		/// Copy constructor.
		/// @param in The ServerSocketStream to copy.
		ServerSocketStream(const ServerSocketStream& in);
		#else
		/// Move constructor.
		/// @param in The ServerSocketStream to move.
		ServerSocketStream(ServerSocketStream&& in);
		#endif

		void CloseSocket();

		/// Destructor
		~ServerSocketStream();

		/// Listens indefinitely for a connection on a port
		SocketStream ListenForConnection() throw (NoConnection, CannotConnect);

		/// Assignment operator
		#if __cplusplus < 201103L
		ServerSocketStream& operator=(const ServerSocketStream& in);
		#else
		ServerSocketStream& operator=(ServerSocketStream&& in);
		#endif

	private:
		/// Class that represents the actual socket
		class ServerSocket;
		ServerSocket* mSocket;
};

#endif

