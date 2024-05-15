#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */

TcpServer::TcpServer( std::string &serverStr) : Server(serverStr), _newSocket()
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0)
        throw SocketError();
    _address.sin_family = AF_INET;
    _address.sin_port = _port;
    _address.sin_addr.s_addr = _ip;
    if (bind(_socket, (sockaddr *)&_address, sizeof(_address)) < 0)
        throw ConnectError();
    std::cout << "Starting Server at " << _ip << " on port " << _port;
}

void	TcpServer::ServerAnswer()
{
	unsigned long		sent;
	
	std::string	header = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";

	std::stringstream itoa;
	itoa << outputErrorPage(500).size();
	header.append(itoa.str());

	header.append("\n\n");
	
	std::string	answer = header + outputErrorPage(500);

	sent = write(_newSocket, answer.c_str(), answer.size());
	if (sent != answer.size())
		throw	AnswerFailure();
}

void	TcpServer::ServerListen()
{
	if (listen(_socket, _maxConnections) < 0)
		throw ListenFailed();
    std::ostringstream	stream;
	int	bytesReceived = 0;
	while (bytesReceived >= 0)
	{
		//	accept connection
		_newSocket = accept(_socket, (sockaddr *)&_address, &_addressLen);
		//	errcheck
		if (_newSocket < 0)
			throw NewSocketError();
//	dogshit buffer
		char buffer[155555] = {0};
        bytesReceived = read(_newSocket, buffer, 155555);
		//	errcheck
		if (bytesReceived < 0)
			throw IncomingBytesFailed();
		//	debug: show incoming request:
		std::cout << buffer << std::endl;
		//	answer
		ServerAnswer();
        close(_newSocket);
	}
}

TcpServer::~TcpServer()
{
    close(_socket);
}