
#include "Server.hpp"

Server::Server( void )
{
}

Server::Server()
{
}

Server::~Server( )
{
}

void	Server::ServerListen()
{
	if (listen(_tcpServer._socket, _maxConnections) < 0)
		throw ListenFailed();
    std::ostringstream	stream;
	int	bytesReceived = 0;
	while (bytesReceived >= 0)
	{
		//	accept connection
		_tcpServer._newSocket = accept(_tcpServer._socket, (sockaddr *)&_tcpServer._address, &_tcpServer._addressLen);
		//	errcheck
		if (_tcpServer._newSocket < 0)
			throw NewSocketError();
//	dogshit buffer
		char buffer[155555] = {0};
        bytesReceived = read(_tcpServer._newSocket, buffer, 155555);
		//	errcheck
		if (bytesReceived < 0)
			throw IncomingBytesFailed();
		//	debug: show incoming request:
		std::cout << buffer << std::endl;
		//	answer
		ServerAnswer();
        close(_tcpServer._newSocket);
	}
}

void	Server::ServerAnswer()
{
	long		sent;

	std::string	header = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + outputErrorPage(500).size();

	header.append("\n\n");
	
	std::string	answer = header + outputErrorPage(500);

	sent = write(_tcpServer._newSocket, answer.c_str(), answer.size());
	if (sent != answer.size())
		throw	AnswerFailure();
}

std::string Server::outputErrorPage(int id)
{
	std::string strFile = returnFileStr(_httpError.getInfo(id).file.c_str());
	if (strFile.empty())
	{
		strFile.append("<!DOCTYPE html><html style=\"background-color: black; color: white; text-align: center;font-family: system-ui;\"><head><title>");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("</title><img src=\"https://i.imgur.com/qWMCwWS.gif\"/><h1>");
		std::stringstream itoa;
		itoa << id;
		strFile.append(itoa.str());
		strFile.append(" - ");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("</h1><h3>");
		strFile.append(_httpError.getInfo(id).info);
		strFile.append("</h3>contact your local admin at ");
		strFile.append(_contact);
		strFile.append("</body></html>");
	}
	return strFile;
}