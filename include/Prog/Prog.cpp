
#include "Prog.hpp"

Prog::Prog( void )
{

}

Prog::~Prog()
{
	for (std::vector< Server * >::iterator it = _servers.begin(); it != _servers.end(); it++)
		delete *it;
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
	size_t	startPos = getChunkStart(iss, fileContent, "server");
	while (startPos != std::string::npos)
	{
		size_t	endPos = getChunkEnd(fileContent, startPos);
		//std::cout << "[DEBUG]" << startPos << " - " << endPos << std::endl;
		std::string	serverStr = fileContent.substr(startPos, endPos);
		fileContent.erase(startPos, endPos);
		//std::cout << "[DEBUG]" << serverStr;
		Server	*nServer = new Server(serverStr);
		_servers.push_back(nServer);
		std::istringstream niss(fileContent);
		startPos = getChunkStart(niss, fileContent, "server");
	}
}

void	Prog::parseFile( char *filePath )
{
	std::string fileContent = returnFileStr( filePath );

	removeComment( fileContent );
	getServerStr( fileContent );
	if (!_servers.size())
		throw NoServerFound();
}
