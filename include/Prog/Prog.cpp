
#include "Prog.hpp"

Prog::Prog( void )
{

}

Prog::~Prog()
{
	for (std::vector< TcpServer * >::iterator it = _servers.begin(); it != _servers.end(); it++)
		delete *it;
}

void	Prog::startAllServers( void )
{
	for (std::vector<TcpServer *>::iterator it = _servers.begin(); it != _servers.end(); it++)
		(*it)->ServerStart();
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
