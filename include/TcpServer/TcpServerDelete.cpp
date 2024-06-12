
#include "TcpServer.hpp"

void	TcpServer::deleteFile( std::string &res )
{
	if (std::remove( res.c_str() ))
	{
		addLog( "File: " + res + " can't be deleted, no such file or directory.");
		ServerAnswerError(204);
	}
	else
	{
		addLog( "File: " + res + " has been deleted.");
		ServerAnswerError(200);
	}
}

void	TcpServer::ServerAnswerDelete( HttpHeader &header )
{
	std::vector< Route >	route = getRoute();
	std::string	res;

	for (std::vector<Route>::iterator it = route.begin(); it != route.end(); it++)
	{
		if (std::find((*it).getMethods().begin(), (*it).getMethods().end(), header.getMethod())\
			!= (*it).getMethods().end())
		{
			checkValidRoute(header, *it, res);
			if (!res.empty())
			{
				deleteFile( res);
				return ;
			}
		}
		else if (it + 1 == route.end())
		{
			ServerAnswerError(405);
			return ;
		}
	}
	ServerAnswerError(404);
}