
#include "Prog.hpp"

Prog::Prog( bool &serverRunning, char **env ) : _serverRunning(serverRunning), _env(env)
{

}

Prog::~Prog()
{
	for (std::vector< TcpServer * >::iterator it = _servers.begin(); it != _servers.end(); it++)
		delete *it;
}

void	Prog::startAllServers( void )
{
	if (_servers.size() > FD_SETSIZE) /* FD_SETSIZE is the limit set by select, see man select -> DESCRIPTION */
		throw TooMuchServers();
	for (std::vector<TcpServer *>::iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		if (listen((*it)->getSocket(), _servers.size()) < 0)
			throw ListenFailed();
	}
	ServerRoutine();
}

void	Prog::ServerRoutine( void )
{
	while (_serverRunning)
	{
		FD_ZERO(&fdSet);
		for (std::vector<TcpServer *>::iterator it = _servers.begin(); it != _servers.end(); it++)
			FD_SET((*it)->getSocket(), &fdSet);
		if (select(_servers.back()->getSocket() + 1, &fdSet, 0, 0, 0) < 0)
		{
			if (_serverRunning)
				throw SelectFailed();
			return ;
		}
		for (std::vector<TcpServer *>::iterator it = _servers.begin(); it != _servers.end(); it++)
		{
			if (FD_ISSET((*it)->getSocket(), &fdSet))
				(*it)->ServerListen();
		}
	}
	FD_ZERO(&fdSet);
}

std::string	Prog::getServerStrDebug( void )
{
	std::string	res;
	for (std::vector< TcpServer * >::iterator it = _servers.begin(); it != _servers.end(); it++)
		res.append((*it)->getVarStr());
	return (res);
}

void	Prog::removeComment( std::string &fileContent )
{
	size_t	end = 0;
	size_t	start = fileContent.find("#", 0);
	while (start != std::string::npos)
	{
		end = fileContent.find("\n", start);
		if (end)
			fileContent.erase(start, (end - start));
		start = fileContent.find("#", start);
	}
}

void	Prog::getServerStr( std::string &fileContent )
{
	std::istringstream	iss(fileContent);
	size_t	startPos = getChunkStart(iss, fileContent, "server[");
	while (startPos != std::string::npos)
	{
		size_t	endPos = getChunkEnd(fileContent, startPos);
		if (startPos == 0)
			endPos++;
		std::string	serverStr = fileContent.substr(startPos, endPos);
		fileContent.erase(startPos, endPos);
		TcpServer	*nServer = new TcpServer(serverStr);
		_servers.push_back(nServer);
		std::istringstream niss(fileContent);
		startPos = getChunkStart(niss, fileContent, "server[");
	}
}

void	Prog::parseFile( char *filePath )
{
	std::string	strFilePath(filePath);
	if (strFilePath.find(".conf") == std::string::npos) /*	Prevent processing random files	*/
		throw FileNameError();
	std::string fileContent = returnFileStr( filePath );
	if (fileContent.empty())
		throw UnableToOpenFile();
	/*	if processing huge files here can be very long...	*/
	removeComment( fileContent );
	getServerStr( fileContent );
	if (!_servers.size())
		throw NoServerFound();
}
