
#pragma once

# include <sys/socket.h>
# include <iostream>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "../Exception/Exception.hpp"

// Create and bind a socket
class Socket
{
	protected:

		int	_socket;

	public:

		Socket( std::string ip, int port );
		Socket( Socket &val );
		~Socket();

		Socket	&operator=( Socket &val );

		int	getSocket( void ) { return _socket; }
};
