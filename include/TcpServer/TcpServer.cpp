#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */


std::string     buildHeader(std::string extension, int errorcode, int contentSize)
{
    HttpError   error;
    std::string returnStr("HTTP/1.1 ");

	(void) extension;
    returnStr.append(" " + ft_itoa(errorcode));
    returnStr.append(" " + error.getInfo(errorcode).type);
    returnStr.append("\r\n");
    returnStr.append("content-type: text/html\r\n"); // "content-type: " + getMimeType(extension) + "\r\n"
    returnStr.append("content-length: " + ft_itoa(contentSize) + "\r\n");
    returnStr.append("connection: close\r\n");
    returnStr.append("\n");

    return returnStr;
}

TcpServer::TcpServer( std::string &serverStr ) : Server(serverStr), _newSocket(), _addressLen(sizeof(_address))
{
}

void	TcpServer::ServerStart()
{
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket < 0)
		throw SocketError();
	//	end default
	_address.sin_family = AF_INET;
	_address.sin_port = ntohs(_port);
		_address.sin_addr.s_addr = inet_addr(_ipStr.c_str());
	//_address.sin_addr.s_addr = ntohl(_ip);
	if (bind(_socket, (sockaddr *)&_address, _addressLen) < 0)
		throw ConnectError();
	std::cout << "Starting server: " << _serverName <<  " at " << _ipStr << " on port " << _port << std::endl;
	ServerListen();
}

void	TcpServer::ServerAnswer(std::string incoming)
{
	unsigned long		sent;
	std::string			output;

    //  build output answer
	(void) incoming;
    //  build header based on answer
	HttpHeader			header(output);
	output.insert(0, "\n\n");
	output.insert(0, header.buildHeader());


	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
}

bool	TcpServer::checkValidRoute( std::string &method, std::string &path, Route &route, bool is_end)
{
	(void) path;
	if (std::find(route.getMethods().begin(), route.getMethods().end(), method) != route.getMethods().end())
	{
		std::string	filename;
		if (route.getRedirection().empty())
		{
			filename = path;
			if (filename.find(route.getPath()) == std::string::npos)
				return (false);
			filename.erase(filename.find(route.getPath()), route.getPath().size() - 1);
			std::cout << filename << std::endl;
			std::string	fullPath = BuildRelativePath(_root, route.getPath(), filename);
			if (!access( fullPath.c_str() , R_OK))
			{
				std::string	awnser = returnFileStr(fullPath);
				awnser.insert(0,  buildHeader(filename.substr(filename.find_last_of("."), std::string::npos), 200, awnser.size()));
				send(_newSocket, awnser.c_str(), awnser.size(), 0);
				close (_newSocket);
				exit(0);
			}
		}


		return (true);
	}
	else if (is_end)
		ServerAnswerError(405);
	return (true);
	
}

void	TcpServer::ServerAnswerGet(std::string method, std::string path)/* in the future &HttpHeader 
																		with all the infos inside */
{
	std::vector< Route >	route = getRoute();

	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); it++)
	{
		if (checkValidRoute(method, path, *it, (it + 1 == route.end())))
			return ;
	}
}

void	TcpServer::ServerAnswerError(int id)
{
	unsigned long		sent;
	std::string			output(outputErrorPage(id));
    HttpHeader          header(output, id);

	output.insert(0, "\n\n");
	output.insert(0, header.buildHeader());
	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
    close(_newSocket);
	exit(1);
}

void	TcpServer::ServerListen()
{
	if (listen(_socket, _maxConnections) < 0)
		throw ListenFailed();
	int	bytesReceived = 0;
	while (bytesReceived >= 0 && bytesReceived <= _maxConnections)
	{
		_newSocket = accept(_socket, (sockaddr *)&_address, &_addressLen);
		int pid = fork();
		if (!pid)
		{
			if (_newSocket < 0)
				throw NewSocketError();
			char buffer[_maxHeaderSize + 2];
			std::string		incoming;
			bytesReceived = recv(_newSocket, buffer, _maxHeaderSize + 1, 0);
			incoming.append(buffer);
			//	parse received http header
			/*while (readed > 0)
			{
				readed = read(_newSocket, buffer, _maxHeaderSize);
				incoming.append(buffer);
			} */
			std::cout << incoming << std::endl;

			if (bytesReceived < 0)
				throw IncomingBytesFailed();
			else if (bytesReceived > _maxHeaderSize)
				ServerAnswerError(413);
			else 
				ServerAnswerGet("GET", "test/rien.htm");
			close(_newSocket);
			exit(0);
		}
	}
}

TcpServer::~TcpServer()
{
    //close(_socket);
}