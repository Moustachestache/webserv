#include "TcpServer.hpp"

/* TcpServer::TcpServer() : TcpServer(0, 80) 
{
    _addressLen = (sizeof(_address));
//  default constructor calls TcpServer with default value :
//  ip = 0.0.0.0 and port = 80
//  but really this should never happen lol
} */

TcpServer::TcpServer( std::string &serverStr ) :	Server(serverStr), \
													_socket(_ip, _port), \
													_newSocket(), \
													_addressLen(sizeof(_address))
{
	std::cout << "Starting server: " << _serverName <<  " at " << _ipStr << " on port " << _port << std::endl;
	addLog("Starting server: " + _serverName + " at " + _ipStr + " on port " + ft_itoa(_port));
}

// Copy constructor
TcpServer::TcpServer( TcpServer &val ) :	Server(val), \
											_socket(_ip, _port), \
											_newSocket(val._newSocket), \
											_address(val._address), \
											_addressLen(val._addressLen)
{

}

TcpServer	&TcpServer::operator=( TcpServer &cpy )
{
	if (&cpy != this)
	{
		_socket = cpy._socket;
		_newSocket = cpy._newSocket;
		_address = cpy._address;
		_addressLen = cpy._addressLen;
		_httpError = cpy._httpError;
		_ipStr = cpy._ipStr;
		_ip = cpy._ip;
		_contact = cpy._contact;
		_port = cpy._port;
		_serverName = cpy._serverName;
		_root = cpy._root;
		_maxHeaderSize = cpy._maxHeaderSize;
		_requestSize = cpy._requestSize;
		_route = cpy._route;
		_errorLog = cpy._errorLog;
	}
	return (*this);
}

void	TcpServer::ifExistSend( Route &route, std::string &filename, HttpHeader &header, std::string &res )
{
	std::string	fullPath = BuildRelativePath(_root, route.getPath(), filename);
	// add check of "../"
	DIR					*openDir = opendir(fullPath.c_str());

	(void) header;
	if ((!fullPath.empty() && fullPath.at(fullPath.size() - 1) == '/')\
				&& openDir) /* Make sure there is a '/' and the folder is open */
		res = fullPath;
	else if ((!fullPath.empty() && fullPath.at(fullPath.size() - 1) != '/')\
				&& !openDir && !access( fullPath.c_str() , R_OK)) /* make sure there is no '/'
							and make sure no dir got the same name and the file is accessible */
		res = fullPath;
	if (openDir)
		closedir(openDir);
}

void	TcpServer::checkValidRoute( HttpHeader &header, Route &route, std::string &res ) // 
{
	if (route.getRedirection().empty())
	{
		std::string filename = header.getFile();
		
		if (filename.find(route.getPath()) == std::string::npos)
			return ;
		filename.erase(filename.find(route.getPath()), route.getPath().size() - 1);
		ifExistSend( route, filename, header, res );
	}
	else
	{
		std::string filename = header.getFile();
		if (filename.find(route.getRedirection()) == std::string::npos)
			return ;
		filename.erase(filename.find(route.getRedirection()), route.getRedirection().size() - 1);
		ifExistSend( route, filename, header, res );
	}
}

void	TcpServer::ServerAnswerPost( HttpHeader &header )
{
//	rien
	//std::cout << header.getArgs()["Referer"] << std::endl;
	(void) header;
	ServerAnswerError(200);
}

void	TcpServer::ServerAnswerError(int id)
{
	unsigned long		sent;
	std::string			output(outputErrorPage(id));

	addLog( "Server answer: " + ft_itoa(id) );
	output.insert(0, buildHeader(".html", id, output.size(), getRoute()));
	sent = write(_newSocket, output.c_str(), output.size());
	if (sent != output.size())
		throw	AnswerFailure();
	return ;
}

void	TcpServer::ServerListen()
{
	_newSocket = accept(getSocket(), (sockaddr *)&_address, &_addressLen);
	if (_newSocket < 0)
		throw NewSocketError();
	
	HttpHeader		header(_newSocket, *this);

	addLog( "New incoming connection on server " + _serverName + ": " + header.getMethod() + " " + header.getFile() );
	if (header.getError() > 0)
		ServerAnswerError(header.getError());
	else if (isCgi(getRoute(), header) == true)
		execCgi(header, true_path(getRoute(), header), getRoute() );
	else if (!header.getMethod().compare("GET"))
		ServerAnswerGet(header);
	else if (!header.getMethod().compare("DELETE"))
		ServerAnswerDelete(header);
	else if (!header.getMethod().compare("POST"))
		ServerAnswerPost(header);
	else
		ServerAnswerError(405); /*	Returns all allowed methods	*/
	close(_newSocket);
	_newSocket = 0;
}

TcpServer::~TcpServer()
{
	addLog("Closing server: " + _serverName + " at " + _ipStr + " on port " + ft_itoa(_port));
	if (_newSocket)
		close(_newSocket);
}