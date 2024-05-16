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
//	default for testing
	_ipStr = "0.0.0.0";
	_port = 8081;
	_maxHeaderSize = 14;
//	end default
    _address.sin_family = AF_INET;
    _address.sin_port = ntohs(_port);
    _address.sin_addr.s_addr = inet_addr(_ipStr.c_str());
    if (bind(_socket, (sockaddr *)&_address, _addressLen) < 0)
        throw ConnectError();
    std::cout << std::endl << "Starting Server at " << _ipStr << " on port " << _port << std::endl;
	ServerListen();
}

void	TcpServer::ServerAnswer(std::string incoming)
{
	unsigned long		sent;
	HttpHeader			header(incoming);
	std::string			output;


	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
}

void	TcpServer::ServerAnswerError(int id)
{
	unsigned long		sent;
	HttpHeader			header(id);
	std::string			output;

	output.append(header.buildHeader());
	output.append(outputErrorPage(id));
	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
}

void	TcpServer::ServerListen()
{
	if (listen(_socket, _maxConnections) < 0)
		throw ListenFailed();
	int	bytesReceived = 0;
	while (bytesReceived >= 0 && bytesReceived <= _maxConnections)
	{
		_newSocket = accept(_socket, (sockaddr *)&_address, &_addressLen);
		//	errcheck
		if (_newSocket < 0)
			throw NewSocketError();
		char buffer[_maxHeaderSize];
		std::string		incoming;
		int				readed = 1;
		while (readed >= 0)
		{
			readed = read(_newSocket, buffer, _maxHeaderSize);
			incoming.append(buffer);
		}
		std::cout << incoming;
		if (bytesReceived < 0)
			throw IncomingBytesFailed();
		if (bytesReceived > _maxHeaderSize)
			ServerAnswerError(203);
		ServerAnswer(incoming);
        close(_newSocket);
	}
}

TcpServer::~TcpServer()
{
    close(_socket);
}