
#include "Route.hpp"

Route::Route( void )
{
	
}

Route::Route( std::string &routeStr )
{
	//std::cout << routeStr;
	getAllCgi( routeStr );
}

Route::~Route( )
{
	
}

void	Route::getAllCgi( std::string &routeStr )
{
	size_t	startPos = routeStr.find("CGI");
	while (startPos != std::string::npos)
	{
		std::string	cgiStr = routeStr.substr(startPos);
		size_t	endPos = getChunkEnd(cgiStr, 0);
		cgiStr.resize(endPos);
		//std::cout << errorStr << std::endl;
		
		routeStr.erase(startPos, cgiStr.size());
		startPos = routeStr.find("CGI");
	}
}