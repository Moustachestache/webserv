
#include "Exception.hpp"

const char	*UnableToOpenFile::what( void ) const throw()
{
	return ("Error: unable to open config file.");
}

const char	*NoServerFound::what( void ) const throw()
{
	return ("Error: no server found in config file.");
}

const char	*WrongWord::what( void ) const throw()
{
	return ("");
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
	return ("Error: variable cannot be empty.");
}

const char	*WrongHttpErrorNumber::what( void ) const throw()
{
	return ("Error: unexpected http-error number in config file.");
}