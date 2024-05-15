
#include "Exception.hpp"

const char	*UnableToOpenFile::what( void ) const throw()
{
	return ("Error: unable to open the file.");
}

const char	*NoServerFound::what( void ) const throw()
{
	return ("Error: no server found in the config.");
}

const char	*WrongWord::what( void ) const throw()
{
	return ("");
}

const char	*BracketsError::what( void ) const throw()
{
	return ("Error: while parsing the brackets.");
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