
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
	private:

		int	_socket;

	public:

		/*		CONSTRUCTORS/DESTRUCTOR		*/

		Socket( unsigned int ip, int port );
		Socket( Socket &val );
		~Socket();

		/*		OPERATOR OVERLOADING		*/

		Socket	&operator=( Socket &val );

		/*		GETTER		*/

		int	getSocket( void ) { return _socket; }
};
