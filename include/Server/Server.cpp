
#include "Server.hpp"

Server::Server( void )
{
	
}

Server::Server( std::string &serverStr )
{
	checkServerHeader( serverStr );
	getAllRoutes( serverStr, "ROUTE" );
	getAllErrors( serverStr, "ERROR_STATUS" );
	getAllVariables( serverStr );
}

Server::~Server( )
{
	for (std::vector< Route * >::iterator it = _route.begin(); it != _route.end(); it++)
		delete *it;
}

void	Server::assignError( std::istringstream &iss )
{
	int	id;
	std::string	sep;
	std::string word;
	if (!(iss >> id))
		throw WrongVariableAssignment();
	if (!(iss >> sep))
		throw WrongVariableAssignment();
	else if (sep.compare("="))
		throw WrongVariableAssignment();
	else if (!(iss >> word))
		throw WrongVariableAssignment();
	_httpError.addErrorPage(id, word);
}

void	Server::addError( std::string &errorStr )
{
	std::istringstream	iss(errorStr);
	int	id;
	std::string	sep;
	std::string word;
	while (sep.find("{"))
		iss >> sep;
	while ((iss >> id))
	{
		if (!(iss >> sep))
			throw WrongVariableAssignment();
		else if (sep.compare("="))
			throw WrongVariableAssignment();
		else if (!(iss >> word))
			throw WrongVariableAssignment();
		_httpError.addErrorPage(id, word);
	}
}

void	Server::getAllErrors( std::string &serverStr, std::string name )
{
	size_t	startPos = serverStr.find(name);
	while (startPos != std::string::npos)
	{
		std::string	errorStr = serverStr.substr(startPos);
		size_t	endPos = getChunkEnd(errorStr, 0);
		errorStr.resize(endPos);
		std::cout << errorStr << std::endl;
		addError(errorStr);
		serverStr.erase(startPos, errorStr.size());
		startPos = serverStr.find(name);
	}
}

void	Server::getAllRoutes( std::string &serverStr, std::string name )
{
	size_t	startPos = serverStr.find(name);
	while (startPos != std::string::npos)
	{
		std::string	routeStr = serverStr.substr(startPos);
		size_t	endPos = getChunkEnd(routeStr, 0);
		routeStr.resize(endPos);
		std::cout << routeStr << std::endl;
		Route	*nRoute = new Route(routeStr);
		_route.push_back( nRoute );
		serverStr.erase(startPos, routeStr.size());
		startPos = serverStr.find(name);
	}
}

void	Server::checkServerHeader( std::string &serverStr )
{
	size_t	pos = serverStr.find("server[");
	if (pos == std::string::npos)
		throw	WrongHeader();
	serverStr.erase(0, 7);
	pos = serverStr.find(":");
	if (pos == std::string::npos)
		throw	WrongHeader();
	_ipStr = serverStr.substr(0, pos);
	serverStr.erase(0, pos + 1);
	std::istringstream	iss(serverStr);
	if (!(iss >> _port))
		WrongHeader();
	serverStr.erase(0, (serverStr.find("{") + 1));
}

template < typename V >
void	assignSingleValue( std::istringstream &iss, V &to_assign )
{
	std::string	sep;
	V word;
	if (!(iss >> sep))
		throw WrongVariableAssignment();
	else if (sep.compare("="))
		throw WrongVariableAssignment();
	else if (!(iss >> word))
		throw WrongVariableAssignment();
	to_assign = word;
}

void	Server::getVarContent( std::string &buffer, std::istringstream &iss )
{
	if (!buffer.compare("SERVER_NAME"))
		assignSingleValue(iss, _serverName);
	else if (!buffer.compare("ROOT"))
		assignSingleValue(iss, _root);
	else if (!buffer.compare("REQUEST_SIZE"))
		assignSingleValue(iss, _requestSize);
	else if (!buffer.compare("CONTACT"))
		assignSingleValue(iss, _contact);
	else if (!buffer.compare("REQUEST_SIZE"))
		assignSingleValue(iss, _requestSize);
	else if (!buffer.compare("ERROR_LOG"))
		assignSingleValue(iss, _errorLog);
	else if (!buffer.compare("}"))
		return ;
	else
		throw WrongVariableAssignment();
}

void	Server::getAllVariables( std::string &serverStr )
{
	std::istringstream	iss(serverStr);
	std::string	buffer;
	while (iss >> buffer)
		getVarContent(buffer, iss);
}

std::string Server::outputErrorPage(int id)
{
	std::string strFile = returnFileStr(_httpError.getInfo(id).file.c_str());
	if (strFile.empty())
	{
		strFile.append("<!DOCTYPE html><html style=\"background-color: black; color: white; text-align: center;font-family: system-ui;\"><head><title>");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("</title><img src=\"https://i.imgur.com/qWMCwWS.gif\"/><h1>");
		std::stringstream itoa;
		itoa << id;
		strFile.append(itoa.str());
		strFile.append(" - ");
		strFile.append(_httpError.getInfo(id).type);
		strFile.append("</h1><h3>");
		strFile.append(_httpError.getInfo(id).info);
		strFile.append("</h3>contact your local admin at ");
		strFile.append(_contact);
		strFile.append("</body></html>");
	}
	return strFile;
}
/*
<!DOCTYPE html><html style="background-color: black; color: white; text-align: center;font-family: system-ui;"><head><title>
error
</title><img src="https://i.imgur.com/qWMCwWS.gif"/><h1>
error
</h1><h3>
this is the error text
</h3>contact your local admin at 
$var@$var
</body></html>
*/