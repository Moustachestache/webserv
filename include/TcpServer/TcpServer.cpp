#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */

TcpServer::TcpServer( std::string &serverStr) : Server(serverStr), _newSocket(), _addressLen(sizeof(_address))
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		throw SocketError();
	_ipStr = "0.0.0.0";
	_port = 8081;
    _address.sin_family = AF_INET;
    _address.sin_port = ntohs(_port);
    _address.sin_addr.s_addr = inet_addr(_ipStr.c_str());
    if (bind(_socket, (sockaddr *)&_address, _addressLen) < 0)
        throw ConnectError();
    std::cout << "Starting Server at " << _ipStr << " on port " << _port << std::endl;
	ServerListen();
}

void	TcpServer::ServerAnswer(std::string incoming)
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
		_newSocket = accept(_socket, (sockaddr *)&_address, &_addressLen);
		//	errcheck
		if (_newSocket < 0)
			throw NewSocketError();
//	dogshit buffer
//	must find way for clean buffer
char buffer[155555] = {0};
        bytesReceived = read(_newSocket, buffer, 155555);
		if (bytesReceived < 0)
			throw IncomingBytesFailed();
//	debug: show incoming request:
std::cout << "debug: incoming request:\n"<< buffer << std::endl;
		//	answer
		ServerAnswer(buffer);
        close(_newSocket);
	}
}

TcpServer::~TcpServer()
{
    close(_socket);
}