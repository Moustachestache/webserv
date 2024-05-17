
#include "Route.hpp"

Route::Route( void )
{
	
}

Route::Route( std::string &routeStr ) :	_redirection(""), _listing(false), \
										_allowUpload(false), _sessionTimeout(600)
					/*	Init all members to avoid memory errors while reading them.

	!! Need to check with the team wich value we set in default for each !!	*/
{
	//std::cout << routeStr;
	_path = getHeaderStr(routeStr);
	getAllCgi( routeStr );
	getAllVariables( routeStr );
}

Route::~Route( )
{
	
}

void	assignAllowUpload( std::istringstream &iss, bool &to_assign )
{
	std::string	sep;
	if (!(iss >> sep))
		throw WrongVariableAssignment();
	else if (sep.compare("="))
		throw WrongVariableAssignment();
	else if (!(iss >> sep))
		throw WrongVariableAssignment();
	if (!sep.compare("allow"))
		to_assign = true;
	else
		to_assign = false;
}

void	Route::getVarContentRoute( std::string &line )
{
	std::istringstream	iss(line);
	std::string	word;
	if (!(iss >> word))
		return ;
	if (!word.compare("METHOD"))
		assignMultipleValue(iss, _methods);
	else if (!word.compare("REDIRECTION"))
		assignSingleValue(iss, _redirection);
	else if (!word.compare("LISTING"))
		assignAllowUpload(iss, _listing);
	else if (!word.compare("DEFAULT"))
		assignMultipleValue(iss, _defaultPages);
	else if (!word.compare("ALLOW_UPLOAD"))
		assignAllowUpload(iss, _allowUpload);
	else if (!word.compare("UPLOAD_PATH"))
		assignSingleValue(iss, _uploadPath);
	else if (!word.compare("SESSION_TIMEOUT"))
		assignSingleValue(iss, _sessionTimeout);
	else if (!word.compare("}"))
		return ;
	else
		throw WrongVariableAssignment();
	
}

void	Route::getAllVariables( std::string &routeStr )
{
	std::istringstream	iss(routeStr);
	std::string	line;
	while (std::getline(iss, line))
		getVarContentRoute( line );
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
	nCgi.name = getHeaderStr(cgiStr);
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
		routeStr.erase(startPos, endPos);
		startPos = routeStr.find("CGI");
	}
}