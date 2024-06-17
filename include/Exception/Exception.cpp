
#include "Exception.hpp"

const char	*UnableToOpenFile::what( void ) const throw()
{
	return ("Error: unable to open config file.");
}

const char	*NoServerFound::what( void ) const throw()
{
	return ("Error: no server found in config file.");
}

const char	*BracketsError::what( void ) const throw()
{
	return ("Error: unable to parse brackets in config file.");
}

const char	*WrongHeader::what( void ) const throw()
{
	return ("Error: server chunk must include a valid IP and port.");
}

const char	*WrongVariableAssignment::what( void ) const throw()
{
	return ("Error: wrong variable assignation.");
}

const char	*WrongHttpErrorNumber::what( void ) const throw()
{
	return ("Error: unexpected http-error number in config file.");
}

const char	*SocketError::what( void ) const throw()
{
	return ("Error: unable to create server socket.");
}

const char	*ConnectError::what( void ) const throw()
{
	return ("Error: unable to connect to address.");
}

const char	*ListenFailed::what( void ) const throw()
{
	return ("Error: socket listen failed.");
}

const char	*NewSocketError::what( void ) const throw()
{
	return ("Error: Unable to create new server socket");
}

const char	*IncomingBytesFailed::what( void ) const throw()
{
	return ("Error: failed to read bytes from client connection.");
}

const char	*AnswerFailure::what( void ) const throw()
{
	return ("Error: failed to send response to client.");
}

const char	*FileNameError::what( void ) const throw()
{
	return ("Error: config file name must have '.conf' extension.");
}

const char	*WrongPath::what( void ) const throw()
{
	return ("Error: root path cannot start with a \"/\"");
}

const char	*NoMethod::what( void ) const throw()
{
	return ("Error: server route must have at least one HTTP method.");
}

const char	*NoRouteDefined::what( void ) const throw()
{
	return ("Error: server must have at least one route.");
}

const char	*TooMuchServers::what( void ) const throw()
{
	return ("Error: please make sure you have less than FD_SETSIZE servers.");
}

const char	*SelectFailed::what( void ) const throw()
{
	return ("Error: select call failed.");
}