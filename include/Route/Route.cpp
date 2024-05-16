
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

void	Route::assignMultipleValue( std::istringstream &iss, std::vector< std::string > &vec )
{
	std::string	str;
	std::getline(iss, str);
	std::istringstream	iss2(str);
	iss2 >> str;
	if (str.compare("="))
		throw WrongVariableAssignment();
	while (iss2 >> str)
		vec.push_back(str);
}

void	Route::getVarContentRoute( std::string &buffer, std::istringstream &iss, Cgi &nCgi )
{
	if (!buffer.compare("PATH"))
		assignSingleValue(iss, nCgi.path);
	else if (!buffer.compare("EXTENSION"))
		assignMultipleValue(iss, nCgi.extention);
	else if (!buffer.compare("}"))
		return ;
	else
		throw WrongVariableAssignment();
}

void	Route::processCgi( std::string &cgiStr )
{
	Cgi	nCgi;
	size_t	startPos = cgiStr.find("[");
	size_t	endPos = cgiStr.find("]");
	nCgi.name = cgiStr.substr(startPos + 1, endPos - startPos - 1);
	startPos = cgiStr.find("{") + 1;
	cgiStr.erase(0, startPos);
	std::istringstream	iss(cgiStr);
	std::string	buffer;
	while (iss >> buffer)
		getVarContentRoute(buffer, iss, nCgi);
	_cgi.push_back(nCgi);
}

void	Route::getAllCgi( std::string &routeStr )
{
	size_t	startPos = routeStr.find("CGI");
	while (startPos != std::string::npos)
	{
		std::string	cgiStr = routeStr.substr(startPos);
		size_t	endPos = getChunkEnd(cgiStr, 0);
		cgiStr.resize(endPos);
		//std::cout << cgiStr << std::endl;
		processCgi(cgiStr);
		routeStr.erase(startPos, cgiStr.size());
		startPos = routeStr.find("CGI");
	}
}