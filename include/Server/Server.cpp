
#include "Server.hpp"

Server::Server( void )
{
	
}

Server::~Server( )
{
	
}

std::string Server::outputErrorPage(int id, std::string host, std::string server)
{
    std::string strFile = returnFileStr(_httpError.getInfo(id).file.c_str());
    if (strFile.empty())
    {
        strFile + "hello";
        strFile + _httpError.getInfo(id).type;
        strFile + "ich bin ein zweibel";
        strFile + _httpError.getInfo(id).info;
    }
    return strFile;
}