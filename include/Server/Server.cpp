
#include "Server.hpp"

Server::Server( void )
{
	
}

Server::Server( std::string &serverStr )
{
	(void) serverStr;
}

Server::~Server( )
{
	
}

std::string Server::outputErrorPage(int id, std::string host, std::string server)
{
	std::string strFile = returnFileStr(_httpError.getInfo(id).file.c_str());
	(void) host, server;
	if (strFile.empty())
	{
		strFile.append("hello");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("ich bin ein zweibel");
		strFile.append(_httpError.getInfo(id).info);
	}
	return strFile;
}