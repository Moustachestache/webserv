
#include "Socket.hpp"

Socket::Socket( unsigned int ip, int port )
{
	// Creating IPv4 socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		throw SocketError();

	sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ip;

	// Binding ip and port
	if (bind(_socket, (struct sockaddr*) &addr, sizeof(addr)) < 0)
		throw ConnectError();
}

Socket::Socket( Socket &val ) : _socket(val._socket)
{

}

Socket::~Socket()
{
	close (_socket);
}

Socket	&Socket::operator=( Socket &val )
{
	_socket = val._socket;
	return (*this);
}