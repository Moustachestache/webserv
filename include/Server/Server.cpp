
#include "Server.hpp"

Server::Server( void )
{
}

Server::Server( std::string &serverStr ) :	_contact("postmaster@"), _port(80), _serverName(""), _root(""), \
											_maxHeaderSize(8192), _requestSize(128), \
											_maxConnections(48), _errorLog("log/errorlog.txt")
					/*	Init all members to avoid memory errors while reading them.

	!! Need to check with the team wich value we set in default for each !!	*/
{
	checkServerHeader( serverStr ); // if not port set 80
	getAllRoutes( serverStr, "ROUTE" );
	getAllErrors( serverStr, "ERROR_STATUS" );
	getAllVariables( serverStr );
	_contact.append(_serverName);
	checkInfo();
}

Server::~Server( )
{
	
}

std::vector< Route >	&Server::getRoute( void )
{
	return (_route);
}

void	Server::checkInfo( void )
{
	/*	Implement all the variable checks here	
		if wrong throw an exception	*/
	if (!isPathRelative(_root))
		throw WrongPath();
	//IP 
	//Port //done in the checkHeaderServer()
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

void	Server::processError( std::string &line )
{
	std::string	id;
	std::string	word;
	std::istringstream	iss(line);
	if (!(iss >> id))
		return ;
	if (!id.compare("}"))
		return ;
	if (!(iss >> word))
		throw WrongVariableAssignment();
	else if (word.compare("="))
		throw WrongVariableAssignment();
	else if (!(iss >> word))
		throw WrongVariableAssignment();
	_httpError.addErrorPage(ft_atoi(id), word);
	std::cout << "[DEBUG] Custom error page added : id=" << id << " - path=" << word << std::endl; /*	DEBUG	*/
	if (iss >> word)
		throw WrongVariableAssignment();
}

void	Server::addError( std::string &errorStr )
{
	getHeaderStr( errorStr );
	std::istringstream	iss(errorStr);
	std::string	line;
	while (std::getline(iss, line))
		processError(line);
}

void	Server::getAllErrors( std::string &serverStr, std::string name )
{
	size_t	startPos = serverStr.find(name);
	while (startPos != std::string::npos)
	{
		std::string	errorStr = serverStr.substr(startPos);
		size_t	endPos = getChunkEnd(errorStr, 0);
		errorStr.resize(endPos);
		//std::cout << errorStr << std::endl;
		addError(errorStr);
		serverStr.erase(startPos, endPos);
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
		//std::cout << routeStr << std::endl;
		_route.push_back( Route(routeStr) );
		serverStr.erase(startPos, endPos);
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
	checkValidIp(_ipStr);
	serverStr.erase(0, pos + 1);
	std::istringstream	iss(serverStr);
	if (!(iss >> _port))
		throw WrongHeader();
	serverStr.erase(0, (serverStr.find("{") + 1));
}

void	Server::getVarContentServer( std::string &line )
{
	std::istringstream	iss(line);
	std::string	word;
	if (!(iss >> word))
		return ;
	if (!word.compare("SERVER_NAME"))
		assignSingleValue(iss, _serverName);
	else if (!word.compare("ROOT"))
		assignSingleValue(iss, _root);
	else if (!word.compare("MAX_HEADER_SIZE"))
		assignSingleValue(iss, _maxHeaderSize);
	else if (!word.compare("REQUEST_SIZE"))
		assignSingleValue(iss, _requestSize);
	else if (!word.compare("CONTACT"))
		assignSingleValue(iss, _contact);
	else if (!word.compare("REQUEST_SIZE"))
		assignSingleValue(iss, _requestSize);
	else if (!word.compare("MAX_CONNECTIONS"))
		assignSingleValue(iss, _maxConnections);
	else if (!word.compare("ERROR_LOG"))
		assignSingleValue(iss, _errorLog);
	else if (!word.compare("}"))
		return ;
	else
		throw WrongVariableAssignment();
}

void	Server::getAllVariables( std::string &serverStr )
{
	std::istringstream	iss(serverStr);
	std::string	line;
	while (std::getline(iss, line))
		getVarContentServer(line);
}

std::string Server::outputErrorPage(int id)
{std::cout << "test" << returnFileStr(_httpError.getInfo(id).file.c_str()) << std::endl;
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